//
//  TMChannel.h
//  Twilio IP Messaging Client
//
//  Copyright (c) 2015 Twilio. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "TMConstants.h"

#import "TMMessages.h"
#import "TMMembers.h"

@class TwilioIPMessagingClient;
@protocol TMChannelDelegate;

/** Representation of an IP Messaging channel. */
@interface TMChannel : NSObject

/** Optional channel delegate */
@property (nonatomic, weak) id<TMChannelDelegate> delegate;

/** The unique identifier for this channel. */
@property (nonatomic, copy, readonly) NSString *sid;

/** The friendly name for this channel. */
@property (nonatomic, copy, readonly) NSString *friendlyName;

/** The messages list object for this channel. */
@property (nonatomic, strong, readonly) TMMessages *messages;

/** The members list object for this channel. */
@property (nonatomic, strong, readonly) TMMembers *members;

/** The current user's status on this channel. */
@property (nonatomic, assign, readonly) TMChannelStatusEnum status;

/** The channel's visibility type. */
@property (nonatomic, assign, readonly) TMChannelTypeEnum type;

/** Return this channel's attributes.
 
 @return The developer-defined extensible attributes for this channel.
 */
- (NSDictionary<NSString *, id> *)attributes;

/** Set this channel's attributes.
 
 @param attributes The new developer-defined extensible attributes for this channel. (Supported types are NSString, NSNumber, NSArray, NSDictionary and NSNull)
 @param completion Completion block that will specify the result of the operation.
 */
- (void)setAttributes:(NSDictionary<NSString *, id> *)attributes
           completion:(TSCompletion)completion;

/** Set this channel's friendly name.
 
 @param friendlyName The new friendly name for this channel.
 @param completion Completion block that will specify the result of the operation.
 */
- (void)setFriendlyName:(NSString *)friendlyName
             completion:(TSCompletion)completion;

/** Join the current user to this channel.
 
 @param completion Completion block that will specify the result of the operation.
 */
- (void)joinWithCompletion:(TSCompletion)completion;

/** Decline an invitation to this channel.
 
 @param completion Completion block that will specify the result of the operation.
 */
- (void)declineInvitationWithCompletion:(TSCompletion)completion;

/** Leave the current channel.
 
 @param completion Completion block that will specify the result of the operation.
 */
- (void)leaveWithCompletion:(TSCompletion)completion;

/** Destroy the current channel, removing all of its members.
 
 @param completion Completion block that will specify the result of the operation.
 */
- (void)destroyWithCompletion:(TSCompletion)completion;

/** Indicates to other users and the backend that the user is typing a message to this channel. */
- (void)typing;

@end

/** This protocol declares the IP Messaging client delegate methods. */
@protocol TMChannelDelegate <NSObject>
@optional
/** Called when this channel is changed.
 
 @param client The IP Messaging client.
 @param channel The channel.
 */
- (void)ipMessagingClient:(TwilioIPMessagingClient *)client channelChanged:(TMChannel *)channel;

/** Called when this channel is deleted.
 
 @param client The IP Messaging client.
 @param channel The channel.
 */
- (void)ipMessagingClient:(TwilioIPMessagingClient *)client channelDeleted:(TMChannel *)channel;

/** Called when this channel has a new member join.
 
 @param client The IP Messaging client.
 @param channel The channel.
 @param member The member.
 */
- (void)ipMessagingClient:(TwilioIPMessagingClient *)client channel:(TMChannel *)channel memberJoined:(TMMember *)member;

/** Called when this channel has a member modified.
 
 @param client The IP Messaging client.
 @param channel The channel.
 @param member The member.
 */
- (void)ipMessagingClient:(TwilioIPMessagingClient *)client channel:(TMChannel *)channel memberChanged:(TMMember *)member;

/** Called when this channel has a member leave.
 
 @param client The IP Messaging client.
 @param channel The channel.
 @param member The member.
 */
- (void)ipMessagingClient:(TwilioIPMessagingClient *)client channel:(TMChannel *)channel memberLeft:(TMMember *)member;

/** Called when this channel receives a new message.
 
 @param client The IP Messaging client.
 @param channel The channel.
 @param message The message.
 */
- (void)ipMessagingClient:(TwilioIPMessagingClient *)client channel:(TMChannel *)channel messageAdded:(TMMessage *)message;

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

@end
