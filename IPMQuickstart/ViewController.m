//
//  ViewController.m
//  IPMQuickstart
//
//  Created by Siraj Raval on 11/3/15.
//  Copyright © 2015 Siraj Raval. All rights reserved.
//

#import "ViewController.h"
#import "IPMessagingManager.h"



@interface ViewController ()<UITextFieldDelegate, TwilioIPMessagingClientDelegate>
@property (weak, nonatomic) IBOutlet UITextField *usernameField;
@property (weak, nonatomic) IBOutlet UITextField *topicField;
@property (weak, nonatomic) IBOutlet UIButton *addMemberButton;
@property (weak, nonatomic) IBOutlet UIButton *sendMessageButton;

@property (nonatomic, strong) TMChannels *channelsList;
@property (nonatomic, strong) NSMutableOrderedSet *channels;
@property (nonatomic, strong) TMChannel *channel;

@property (nonatomic, strong) UIActivityIndicatorView *indicator;



@end

@implementation ViewController


#pragma initialize UI elements

- (void)viewDidLoad {
    [super viewDidLoad];
    [self initUI];
    
}

-(void) initUI {
    
    
    //start with hidden buttons
    self.sendMessageButton.hidden = YES;
    self.addMemberButton.hidden = YES;
    
    
    //create event listeners for the fields
    [self.usernameField addTarget:self
                           action:@selector(usernameFieldChanged:)
                 forControlEvents:UIControlEventEditingChanged];
    
    [self.topicField addTarget:self
                        action:@selector(topicFieldChanged:)
              forControlEvents:UIControlEventEditingChanged];
    [self.topicField addTarget:self
                        action:@selector(login)
              forControlEvents:UIControlEventEditingDidEndOnExit];
    
    
    //initialize an activity indicator
    self.indicator = [[UIActivityIndicatorView alloc]initWithActivityIndicatorStyle:UIActivityIndicatorViewStyleGray];
    self.indicator.frame = CGRectMake(150.0, 150.0, 80.0, 80.0);
    self.indicator.center = self.view.center;
    self.indicator.color = [UIColor whiteColor];
    [self.view addSubview:self.indicator];
    [self.indicator bringSubviewToFront:self.view];
    [UIApplication sharedApplication].networkActivityIndicatorVisible = TRUE;
}

- (void)didReceiveMemoryWarning {
    [super didReceiveMemoryWarning];
    // Dispose of any resources that can be recreated.
}


-(void) usernameFieldChanged:(UITextField *)sender {
    NSLog(@"%@", sender.text);
}

-(void) topicFieldChanged:(UITextField *)sender {
    NSLog(@"%@", sender.text);
}

#pragma mark identity setup

-(BOOL) login {
    if (self.usernameField.text && [self.topicField.text length] > 0) {
        [self.indicator startAnimating];
        NSLog(@"the user is %@ and the topic is %@", self.usernameField.text, self.topicField.text);
        [[IPMessagingManager sharedManager] loginWithIdentity:self.usernameField.text];
        [[IPMessagingManager sharedManager] storeTopic:self.topicField.text];
        TwilioIPMessagingClient *client = [[IPMessagingManager sharedManager] client];
        if (client) {
            client.delegate = self;
            [self populateChannels];
        }
        
    }
    return YES;
}

#pragma mark messaging actions

- (IBAction)sendMessage:(id)sender {
    NSLog(@"sending message");
    TMMessage *message = [self.channel.messages createMessageWithBody:@"Hi"];
    [self.channel.messages sendMessage:message
                            completion:^(TMResultEnum result) {
                                if (result == TMResultFailure) {
                                    NSLog(@"Message Failed to send.");
                                } else {
                                    NSLog(@"Message succesfully sent!");
                                }
                            }];
}


#pragma mark member actions

- (IBAction)addMember:(id)sender {
        
        [self.channel.members inviteByIdentity:@"bob"
                                    completion:^(TMResultEnum result) {
                                        if (result == TMResultSuccess) {
                                            NSLog(@"User invited!");
                                        } else {
                                            NSLog(@"User could not be invited.");
                                        }
                                    }];
}

#pragma mark channel actions

- (void)populateChannels {
    self.channelsList = nil;
    self.channels = nil;
    
    dispatch_async(dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0), ^{
        [[[IPMessagingManager sharedManager] client] channelsListWithCompletion:^(TMResultEnum result, TMChannels *channelsList) {
            if (result == TMResultSuccess) {
                self.channelsList = channelsList;
                
                dispatch_async(dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0), ^{
                    [self.channelsList loadChannelsWithCompletion:^(TMResultEnum result) {
                        if (result == TMResultSuccess) {
                            self.channels = [[NSMutableOrderedSet alloc] init];
                            [self.channels addObjectsFromArray:[self.channelsList allObjects]];
                            [self sortChannels];
                            
                            dispatch_async(dispatch_get_main_queue(), ^{
                                
                                BOOL isMatch = false;
                                
                                //OPTION 1
                                //find a channel match
                                for (TMChannel *chan in self.channels) {
                                    if([chan.friendlyName  isEqual: [[IPMessagingManager sharedManager] storedTopic]]) {
                                        self.channels= [[NSMutableOrderedSet alloc] init];
                                        [self.channels addObject:chan];
                                        isMatch = true;
                                        //join it
                                        NSLog(@"Existing channel found");
                                        [self joinChannel:chan];
                                        self.channel = chan;
                                    }
                                }
                                
                                //OPTION 2
                                //if no match, empty the list of channels and create a new channel

                                if(isMatch == false) {
                                    self.channels= [[NSMutableOrderedSet alloc] init];
                                    NSLog(@"No matching channel found");
                                    [self newChannelPrivate:NO];
                                }
                                
                            });
                        } else {
                            NSLog(@"Channel List load FAILED");
                        }
                    }];
                });
            } else {
                dispatch_async(dispatch_get_main_queue(), ^{
                    UIAlertController *alert = [UIAlertController alertControllerWithTitle:@"IP Messaging Demo" message:@"Failed to load channels." preferredStyle:UIAlertControllerStyleAlert];
                    [alert addAction:[UIAlertAction actionWithTitle:@"OK" style:UIAlertActionStyleDefault handler:nil]];
                    [self presentViewController:alert animated:YES completion:nil];
                    
                    self.channelsList = nil;
                    [self.channels removeAllObjects];
                    
                });
            }
        }];
    });
}

- (void)joinChannel:(TMChannel *)channel {
    [channel joinWithCompletion:^(TMResultEnum result) {
        NSLog(@"Channel Joined!");
        NSLog(@"Here are the messages %@", channel.messages.allObjects);
        [self.indicator stopAnimating];
        self.sendMessageButton.hidden = NO;
        self.addMemberButton.hidden = NO;

    }];
}

- (void)sortChannels {
    [self.channels sortUsingDescriptors:@[[[NSSortDescriptor alloc] initWithKey:@"friendlyName"
                                                                      ascending:YES
                                                                       selector:@selector(localizedCaseInsensitiveCompare:)]]];
}

- (void)newChannelPrivate:(BOOL)isPrivate {
                                     [self.channelsList createChannelWithFriendlyName:self.topicField.text
                                                                                 type:isPrivate ? TMChannelTypePrivate : TMChannelTypePublic
                                                                           completion:^(TMResultEnum result, TMChannel *channel) {
                                                                               if (result == TMResultSuccess) {
                                                                                   NSLog(@"Channel created!");
                                                                                   self.channel = channel;

                                                                                   [channel joinWithCompletion:^(TMResultEnum result) {
                                                                                       [channel setAttributes:@{@"topic": @""
                                                                                                                }
                                                                                                   completion:^(TMResultEnum result) {
                                                                                                       NSLog(@"new channel joined!");
                                                                                                       [self.indicator stopAnimating];
                                                                                                       self.sendMessageButton.hidden = NO;
                                                                                                       self.addMemberButton.hidden = NO;

                                                                                                   }];
                                                                                   }];
                                                                               } else {
                                                                                   NSLog(@"Channel creation failed");
                                                                                   [self.indicator stopAnimating];

                                                                               }
                                                                           }];
}

#pragma mark channel delegation methods
- (void)ipMessagingClient:(TwilioIPMessagingClient *)client channelAdded:(TMChannel *)channel {
    
    NSLog(@"Channel added %@", channel);
    
}
- (void)ipMessagingClient:(TwilioIPMessagingClient *)client channelChanged:(TMChannel *)channel   {
    NSLog(@"Channel changed %@", channel);

}
- (void)ipMessagingClient:(TwilioIPMessagingClient *)client channelDeleted:(TMChannel *)channel {
    NSLog(@"Channel deleted %@", channel);
}

#pragma mark message delegation methods
- (void)ipMessagingClient:(TwilioIPMessagingClient *)client channel:(TMChannel *)channel messageAdded:(TMMessage *)message {
    NSLog(@"Message received %@", message);
}


@end
