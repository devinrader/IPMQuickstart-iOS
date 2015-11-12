//
//  TMMessage.h
//  Twilio IP Messaging Client
//
//  Copyright (c) 2015 Twilio. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "TMConstants.h"

/** Representation of a Message on an IP Messaging channel. */
@interface TMMessage : NSObject

/** The unique identifier for this message. */
@property (nonatomic, copy, readonly) NSString *sid;

/** The identity of the author of the message. */
@property (nonatomic, copy, readonly) NSString *author;

/** The body of the message. */
@property (nonatomic, copy, readonly) NSString *body;

/** The timestamp of the message. */
@property (nonatomic, copy, readonly) NSString *timestamp;

@end
