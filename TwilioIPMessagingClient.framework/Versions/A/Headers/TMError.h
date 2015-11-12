//
//  TMError.h
//  Twilio IP Messaging Client
//
//  Copyright (c) 2015 Twilio. All rights reserved.
//

#import <Foundation/Foundation.h>

/** The Twilio IP Messaging error domain. */
FOUNDATION_EXPORT NSString * const TMErrorDomain;

/** The generic error errorCode. */
FOUNDATION_EXPORT NSInteger const TMErrorGeneric;

/** The userInfo key for the error message, if any. */
FOUNDATION_EXPORT NSString * const TMErrorMsgKey;

/** The userInfo key for the error code, if any. */
FOUNDATION_EXPORT NSString* const TMErrorCodeKey;

/** Twilio IP Messaging error object */
@interface TMError : NSError

@end
