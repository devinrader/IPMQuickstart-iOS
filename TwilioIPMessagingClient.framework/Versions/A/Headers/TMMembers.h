//
//  TMMembers.h
//  Twilio IP Messaging Client
//
//  Copyright (c) 2015 Twilio. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "TMConstants.h"
#import "TMMember.h"

/** Representation of an IP Messaging channel's membership list. */
@interface TMMembers : NSObject

/** Obtain an array of members of this channel.
 
 @return An array of TMMember objects representing the membership of the channel.
 */
- (NSArray<TMMember *> *)allObjects;

/** Add specified username to this channel without inviting.
 
 @param identity The username to add to this channel.
 @param completion Completion block that will specify the result of the operation.
 */
- (void)addByIdentity:(NSString *)identity
           completion:(TSCompletion)completion;

/** Invite specified username to this channel.
 
 @param identity The username to invite to this channel.
 @param completion Completion block that will specify the result of the operation.
 */
- (void)inviteByIdentity:(NSString *)identity
              completion:(TSCompletion)completion;

/** Remove specified username from this channel.
 
 @param member The member to remove from this channel.
 @param completion Completion block that will specify the result of the operation.
 */
- (void)removeMember:(TMMember *)member
          completion:(TSCompletion)completion;

@end
