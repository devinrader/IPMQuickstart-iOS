//
//  TMConstants.h
//  Twilio IP Messaging Client
//
//  Copyright (c) 2015 Twilio. All rights reserved.
//

@class TMChannels;
@class TMChannel;

/** Enumeration indicating the success or failure of the operation. */
typedef NS_ENUM(NSInteger, TMResultEnum) {
    TMResultSuccess = 0,        ///< Operation succeeded.
    TMResultFailure             ///< Operation failed.
};

/** Enumeration indicating the user's current status on a given channel. */
typedef NS_ENUM(NSInteger, TMChannelStatusEnum) {
    TMChannelStatusInvited = 0,        ///< User is invited to the channel but not joined.
    TMChannelStatusJoined,             ///< User is joined to the channel.
    TMChannelStatusNotParticipating    ///< User is not participating on this channel.
};

/** Enumeration indicating the channel's visibility. */
typedef NS_ENUM(NSInteger, TMChannelTypeEnum) {
    TMChannelTypePublic = 0,        ///< Channel is publicly visible
    TMChannelTypePrivate            ///< Channel is private and only visible to invited members.
};

// should this be passing NSErrors describing the issue?  what is the user to do in response to a failure?
/** Completion block which will indicate the TMResult of the operation. */
typedef void (^TSCompletion)(TMResultEnum result);

/** Completion block which will indicate the TMResult of the operation and a channels object. */
typedef void (^TMChannelListCompletion)(TMResultEnum result, TMChannels *channelsList);

/** Completion block which will indicate the TMResult of the operation and a channel. */
typedef void (^TMChannelCompletion)(TMResultEnum result, TMChannel *channel);
