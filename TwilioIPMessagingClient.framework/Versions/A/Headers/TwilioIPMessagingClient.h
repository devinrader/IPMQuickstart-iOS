//
//  TwilioIPMessagingClient.h
//  Twilio IP Messaging Client
//
//  Copyright © 2015 Twilio. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "TMConstants.h"
#import "TMError.h"
#import "TMChannels.h"
#import "TMChannel.h"
#import "TMMessages.h"
#import "TMMessage.h"
#import "TMMember.h"

@protocol TwilioIPMessagingClientDelegate;

/** Represents an IP Messaging client connection to Twilio. */
@interface TwilioIPMessagingClient : NSObject

/** Messaging client delegate */
@property (nonatomic, weak) id<TwilioIPMessagingClientDelegate> delegate;

/** The unique identity identifier of this user in the IP Messaging system. */
@property (nonatomic, copy, readonly) NSString *identity;

/** Initialize a new IP Messaging client instance with a token manager.
 
 @param token The authentication token for the user.
 @param delegate Delegate conforming to TwilioIPMessagingClientDelegate for IP Messaging client lifecycle notifications.
 @return New IP Messaging client instance.
 */
+ (TwilioIPMessagingClient *)ipMessagingClientWithToken:(NSString *)token
                                               delegate:(id<TwilioIPMessagingClientDelegate>)delegate;

/** Returns the version of the SDK
 
 @return The IP Messaging client version.
 */
- (NSString *)version;

/** Update auth token before it expires.
 
 @param token The new auth token.
 @param completion Completion block that will specify the result of the operation.
 */
- (void)updateToken:(NSString *)token completion:(TSCompletion)completion;

/** List of channels available to the current user.
 
 @param completion Completion block that will specify the result of the operation and a list of channels visible to the current user.
 */
- (void)channelsListWithCompletion:(TMChannelListCompletion)completion;

/** Register APNS token for push notification updates.
 
 @param token The APNS token which usually comes from 'didRegisterForRemoteNotificationsWithDeviceToken'.
 */
- (void)registerWithToken:(NSData*)token;

/** De-register from push notification updates.
 
 @param token The APNS token which usually comes from 'didRegisterForRemoteNotificationsWithDeviceToken'.
 */
- (void)deregisterWithToken:(NSData *)token;

/** Queue the incoming notification with the messaging library for processing - notifications usually arrive from 'didReceiveRemoteNotification'.
 
 @param notification The incomming notification.
 */
- (void)handleNotification:(NSDictionary *)notification;

/** Cleanly shut down the messaging subsystem when you are done with it. */
- (void)shutdown;

@end

#pragma mark -

/** This protocol declares the IP Messaging client delegate methods. */
@protocol TwilioIPMessagingClientDelegate <NSObject>
@optional

/** Called when the current user has a channel added to their channel list.
 
 @param client The IP Messaging client.
 @param channel The channel.
 */
- (void)ipMessagingClient:(TwilioIPMessagingClient *)client channelAdded:(TMChannel *)channel;

/** Called when one of the current users channels is changed.
 
 @param client The IP Messaging client.
 @param channel The channel.
 */
- (void)ipMessagingClient:(TwilioIPMessagingClient *)client channelChanged:(TMChannel *)channel;

/** Called when one of the current users channels is deleted.
 
 @param client The IP Messaging client.
 @param channel The channel.
 */
- (void)ipMessagingClient:(TwilioIPMessagingClient *)client channelDeleted:(TMChannel *)channel;

/** Called when a channel the current user is subscribed to has a new member join.
 
 @param client The IP Messaging client.
 @param channel The channel.
 @param member The member.
 */
- (void)ipMessagingClient:(TwilioIPMessagingClient *)client channel:(TMChannel *)channel memberJoined:(TMMember *)member;

/** Called when a channel the current user is subscribed to has a member modified.
 
 @param client The IP Messaging client.
 @param channel The channel.
 @param member The member.
 */
- (void)ipMessagingClient:(TwilioIPMessagingClient *)client channel:(TMChannel *)channel memberChanged:(TMMember *)member;

/** Called when a channel the current user is subscribed to has a member leave.
 
 @param client The IP Messaging client.
 @param channel The channel.
 @param member The member.
 */
- (void)ipMessagingClient:(TwilioIPMessagingClient *)client channel:(TMChannel *)channel memberLeft:(TMMember *)member;

/** Called when a channel the current user is subscribed to receives a new message.
 
 @param client The IP Messaging client.
 @param channel The channel.
 @param message The message.
 */
- (void)ipMessagingClient:(TwilioIPMessagingClient *)client channel:(TMChannel *)channel messageAdded:(TMMessage *)message;

/** Called when an error occurs.
 
 @param client The IP Messaging client.
 @param error The error.
 */
- (void)ipMessagingClient:(TwilioIPMessagingClient *)client errorReceived:(TMError *)error;

/** Called when a member of a channel starts typing.
 
 @param client The IP Messaging client.
 @param channel The channel.
 @param member The member.
 */
- (void)ipMessagingClient:(TwilioIPMessagingClient *)client typingStartedOnChannel:(TMChannel *)channel member:(TMMember *)member;

/** Called when a member of a channel ends typing.
 
 @param client The IP Messaging client.
 @param channel The channel.
 @param member The member.
 */
- (void)ipMessagingClient:(TwilioIPMessagingClient *)client typingEndedOnChannel:(TMChannel *)channel member:(TMMember *)member;

/** Called when you are successfully registered for push notifications. 
 
 @param client The IP Messaging client.
 */
- (void)ipMessagingClientToastSubscribed:(TwilioIPMessagingClient *)client;

/** Called when you are successfully registered for push notifications.
 
 @param client The IP Messaging client.
 @param channel The channel for the push notification.
 @param message The message for the push notification.
 */
- (void)ipMessagingClient:(TwilioIPMessagingClient *)client toastReceivedOnChannel:(TMChannel *)channel message:(TMMessage *)message;

/** Called when registering for push notifications fails.
 
 @param client The IP Messaging client.
 @param error An error indicating the failure.
 */
- (void)ipMessagingClient:(TwilioIPMessagingClient *)client toastRegistrationFailedWithError:(TMError *)error;

@end
