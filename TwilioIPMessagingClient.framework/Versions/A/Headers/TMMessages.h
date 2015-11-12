//
//  TMMessages.h
//  Twilio IP Messaging Client
//
//  Copyright (c) 2015 Twilio. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "TMConstants.h"
#import "TMMessage.h"

/** Representation of an IP Messaging channel's message list. */
@interface TMMessages : NSObject

/** Creates a place-holder message which can be populated and sent with sendMessage:completion:

 @param body Body for new message.
 @return Place-holder TMMessage instance
 */
- (TMMessage *)createMessageWithBody:(NSString *)body;

/** Sends a message to the channel.
 
 @param message The message to send.
 @param completion Completion block that will specify the result of the operation.
 */
- (void)sendMessage:(TMMessage *)message
         completion:(TSCompletion)completion;

/** Returns messages received so far from backend, messages are loaded asynchronously so this may not fully represent all history available for channel.
 
 @return Messages received by IP Messaging Client so far for the given channel.
 */
- (NSArray<TMMessage *> *)allObjects;

@end
