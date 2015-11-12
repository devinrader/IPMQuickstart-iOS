//
//  TMChannels.h
//  Twilio IP Messaging Client
//
//  Copyright (c) 2015 Twilio. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "TMConstants.h"

/** Representation of an IP Messaging channel list. */
@interface TMChannels : NSObject

/** Requesting loading of all channels from server to be delivered via delegate callbacks.

 @param completion Completion block that will specify the result.
 */
- (void)loadChannelsWithCompletion:(TSCompletion)completion;

/** Request a list of all channels loaded so far.  Will be an incomplete list until loading completes.
 
 @return The channels loaded so far.
 */
- (NSArray<TMChannel *> *)allObjects;

/** Create a new channel with the specified friendly name.
 
 @param friendlyName Friendly name of the new channel.
 @param channelType Indicates whether or not a channel is public (TMChannelTypePublic) or private (TMChannelTypePrivate). Cannot be changed after channel creation.
 @param completion Completion block that will specify the result of the operation and a reference to the new channel.
 */
- (void)createChannelWithFriendlyName:(NSString *)friendlyName
                                 type:(TMChannelTypeEnum)channelType
                           completion:(TMChannelCompletion)completion;

/** Loads a channel with the specified id.
 
 @param channelId Identifier for the channel.
 @return The channel.
 */
- (TMChannel *)channelWithId:(NSString *)channelId;

@end
