//
//  IPMessagingManager.swift
//  IPMQuickstart
//
//  Created by Devin Rader on 11/25/15.
//  Copyright © 2015 Siraj Raval. All rights reserved.
//

import Foundation
import UIKit

class IPMessagingManager {

    static let sharedManager = IPMessagingManager()
    
    func presentRootViewController() {
        var appDelegate:AppDelegate = UIApplication.sharedApplication().delegate
        if IPMessagingManager.sharedManager().hasIdentity {
            IPMessagingManager.sharedManager().loginWithStoredIdentity()
            appDelegate.window.rootViewController = UIStoryboard(name: "Main")
        } else {
            appDelegate.window.rootViewController = UIStoryboard(name: "Main").instantiateViewControllerWithIdentifier("login")
        }
    }
        
    func hasIdentity() -> Bool {
        return (self.storedIdentity && self.storedIdentity.length > 0)
    }
            
    func loginWithStoredIdentity() -> Bool {
        if ([self.hasIdentity]) {
            return self.loginWithIdentity(self.storedIdentity)
        } else {
            return false
        }
    }
                
    func loginWithIdentity(identity:String) -> Bool {
        if self.client {
            self.logout
        }
                    
        self.storeIdentity(identity)
        
        var token:String = self.tokenForIdentity(identity)
        self.client = TwilioIPMessagingClient.ipMessagingClientWithToken(token, delegate:nil)
                    
        return true;
    }
                    
                    
    func storeTopic(topic:String) {
        NSUserDefaults.standardUserDefaults().synchronize
        NSUserDefaults.standardUserDefaults["topic"]
        print("Topic stored")
    }
    
    func storedTopic() -> String {
        print("Topic retrieved %@", NSUserDefaults.standardUserDefaults["topic"])
                            
        return NSUserDefaults.standardUserDefaults["topic"]
    }

    func logout() {
        self.storeIdentity = nil
        self.client.shutdown
        self.client = nil
    }

    func updatePushToken(token:NSData)  {
        self.lastToken = token
        self.updateIpMessagingClient()
    }

    func receivedNotification(notification:NSDictionary) {
        self.lastNotification = notification
        self.updateIpMessagingClient()
    }

//#pragma mark Push functionality

    func setIpMessagingClient(ipMessagingClient:TwilioIPMessagingClient) {
        self.updateIpMessagingClient
    }

    func updateIpMessagingClient() {
        if (self.lastToken) {
            self.client.registerWithToken(self.lastToken)
            self.lastToken = nil
        }

        if (self.lastNotification) {
            self.client.handleNotification(self.lastNotification)
            self.lastNotification = nil
        }
    }

//#pragma mark Internal helpers


    func tokenForIdentity(identity:String) -> (String) {
        var  identifierForVendor:String = UIDevice.currentDevice().identifierForVendor?.UUIDString
        var bundleIdentifier:String = NSBundle.mainBundle().bundleIdentifier
        var endpoint_id:String = String(format: "%@:%@:%@", identifierForVendor, bundleIdentifier, identity);
        
        var account_sid:String = "ACe3c1d548801318109de50936544bee86";
        var auth_token:String = "130c39d11fff8a25d6f366225c785c0f";
        
        var credential_sid:String = nil; // optional, but if you have created a credential it will start with CR...
        var service_sid:String = "ISabc6f629c809469e8f0cf3c833240676";
        var ttl:long = 1800;
        var urlString:String = String(format:"https://twilio-ip-messaging-token.herokuapp.com/token?account_sid=%@&auth_token=%@&endpoint_id=%@&ttl=%ld&identity=%@&service_sid=%@", account_sid, auth_token, endpoint_id, ttl, identity, service_sid);
        if (credential_sid) {
            urlString = urlString + String(format:"&credential_sid=%@", credential_sid);
        }
        
        return String(contentsOfURL: NSURL(urlString), encoding:NSUTF8StringEncoding, error:nil);
    }
    
    func storeIdentity(identity:String) {
        NSUserDefaults.standardUserDefaults().synchronize;
        return NSUserDefaults.standardUserDefaults()["identity"] = identity;
    }
        
    func storedIdentity() -> String {
        return NSUserDefaults.standardUserDefaults()["identity"];
    }
}