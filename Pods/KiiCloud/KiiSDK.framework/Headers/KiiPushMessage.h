//
//  KiiPushMessage.h
//  KiiSDK-Private
//
//  Created by Riza Alaudin Syah on 1/24/13.
//  Copyright (c) 2013 Kii Corporation. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "KiiReceivedMessage.h"

@class KiiAPNSFields,KiiGCMFields,KiiMQTTFields,KiiBucket,KiiObject,KiiTopic,KiiUser,KiiThing,KiiGroup;

/**
 Class for encapsulating outgoing push notification message
Three types of push message supported by KiiCloud.

 ### GCM restriction for reserved keyword
 Based on Google GCM specification, there are reserved payload keys that should not be used inside data/specific data.
 If GCM is enabled and the data contains one or more reserve keys, an error (code 712) will be thrown.
 Following are the list of GCM reserved keys:
 
    - any key prefix with 'google'
    - from
    - registration_ids
    - collapse_key
    - data
    - delay_while_idle
    - time_to_live
    - restricted_package_name
    - dry_run

 */
@interface KiiPushMessage : NSObject
NS_ASSUME_NONNULL_BEGIN

/** Dictionary representation of APNs received message.
 @deprecated Use <KiiReceivedMessage>
*/
@property(nonatomic,readonly,nullable) NSDictionary* rawMessage __attribute__ ((deprecated()));

/** Dictionary representation of JSON Object with only one-level of nesting. Required if no system-specific “data” fields has been provided for all the systems enabled.	Dictionary with the data that will be sent to all the push systems enabled in this request.
 If gcmFields is defined, the data would be validated for GCM reserved payload keys. 
 */
@property(nonatomic,nullable) NSDictionary* data;

/** APNS-specific fields.
 */
@property(nonatomic,nullable) KiiAPNSFields* apnsFields;

/** GCM-specific fields.
 */
@property(nonatomic,nullable) KiiGCMFields* gcmFields;

/** MQTT-specific fields.
 */
@property(nonatomic,nullable) KiiMQTTFields* mqttFields;

/**Boolean. Not required.
 If true this message will be sent to the devices that have the property "development" to "true" in their installations. Default is true.
 */
@property(nonatomic,nullable) NSNumber* sendToDevelopment;

/** Boolean. Not required.
 If true this message will be sent to the devices that have the property "development" to "false" or nil in their installations. Default is true.
 */
@property(nonatomic,nullable) NSNumber* sendToProduction;

/** String. Not required.
 Value that will optionally indicate what is the type of the message. Event-generated push messages contain it.
 */
@property(nonatomic,nullable) NSString* pushMessageType;

/** Boolean. Not required.
 If true, the appID field will also be sent. Default is false.
 */
@property(nonatomic,nullable) NSNumber* sendAppID;

/**Boolean. Not required.
 If true, send the “sender” field (userID of the user that triggered the notification). Default is true.
 */
@property(nonatomic,nullable) NSNumber* sendSender;

/** Boolean. Not required.
 If true, send the “when” field (when the push message was sent). Default is false.
 */
@property(nonatomic,nullable) NSNumber* sendWhen;

/**Boolean. Not required.
 If true, send the “origin” field (indicates if the message is the result of an event or sent explicitly by someone. Default is false.
 */
@property(nonatomic,nullable) NSNumber* sendOrigin;

/**Boolean. Not required.
 If true, send the “objectScope”-related fields that contain the topic that is the source of this notification. Default is true.
 */
@property(nonatomic,nullable) NSNumber* sendObjectScope;

/** Boolean. Not required.
 If true, send the “topicID” field, which contains the topicID that is the source of this notification. Default is true.
 */
@property(nonatomic,nullable) NSNumber* sendTopicID;

/** Parse incoming APNs message.
 @param userInfo An userInfo instance that received from APNs as a push message.
 @return A KiiPushMessage instance that is associated to the userInfo.
 @deprecated Use <KiiReceivedMessage>
 */
+(KiiPushMessage*) messageFromAPNS:(NSDictionary*) userInfo __attribute__ ((deprecated("Use KiiReceivedMessage instead.")));

/** Constructor method that composes a message for explicit push
 @param apnsfields The message data for APNS
 @param gcmfields The message data for GCM
 @return A KiiPushMessage instance that is associated to the message data.
 @deprecated Use <[KiiPushMessage composeMessage]> instead.
 */
+(KiiPushMessage*) composeMessageWithAPNSFields:(nullable KiiAPNSFields*) apnsfields andGCMFields:(nullable KiiGCMFields*)gcmfields __attribute__ ((deprecated));

/** Constructor method that composes a message for explicit push.
 @param apnsFields The message data for APNS.
 @param gcmFields The message data for GCM.
 @param mqttFields The message data for MQTT.
 @return A KiiPushMessage instance that is associated to the message data.
 @deprecated Use <[KiiPushMessage composeMessage]> instead.
 */
+(instancetype) composeMessageWithAPNSFields:(nullable KiiAPNSFields*) apnsFields
                                   andGCMFields:(nullable KiiGCMFields*)gcmFields
                                  andMQTTFields:(nullable KiiMQTTFields*) mqttFields __attribute__ ((deprecated));

/** Get specific value of received message meta data.
 @param field Enumeration of <KiiMessageField>.
 @return A NSString object that is associated to the message fields.
 @deprecated Use <KiiReceivedMessage>
*/
-(nullable NSString*) getValueOfKiiMessageField:(KiiMessageField) field __attribute__ ((deprecated));

/** Get alert body's text message.
 @return A NSString object of alert body text message.
 @deprecated Use <KiiReceivedMessage>
 */
-(nullable NSString*) getAlertBody __attribute__ ((deprecated));

/** Show simple alert to display alert body's message.
 @param title A alert title to display.
 @deprecated Use <KiiReceivedMessage>
 */
-(void) showMessageAlertWithTitle:(nullable NSString*) title  __attribute__ ((deprecated));

/**Obtain <KiiBucket> based on the information parsed from push message.
 
 The payloads can contain the subscribed bucket informations including the scope and the type (encrypted or not). This API provides convenience methods to obtain <KiiBucket> if the payload contains the subscribed bucket information.
 
 @return <KiiBucket> instance when the event of KiiBucket or <KiiObject> inside <KiiBucket> happened. In other cases returns nil.
 @deprecated Use <KiiReceivedMessage>
 */
-(nullable KiiBucket*) eventSourceBucket __attribute__ ((deprecated));

/**Obtain <KiiObject> based on the information parsed from push message.
 
 The payloads can contain the subscribed bucket's object informations including the scope. This API provides convenience methods to obtain <KiiObject> if the payload contains the object information.
 
 @return <KiiObject> instance when the event of <KiiObject>
 * inside <KiiBucket> happened. In other cases returns nil.
 @deprecated Use <KiiReceivedMessage>
 */
-(nullable KiiObject*) eventSourceObject __attribute__ ((deprecated));

/**Obtain <KiiTopic> based on the information parsed from push message.
 
 The payloads can contain the subscribed topic informations including the scope. This API provides convenience methods to obtain <KiiTopic>  if the payload contains the subscribed topic information.
 
 @return <KiiTopic> instance when the event of KiiTopic (Push to User). In other cases returns nil.
 @deprecated Use <KiiReceivedMessage>
 */
-(nullable KiiTopic*) eventSourceTopic __attribute__ ((deprecated));

/**Obtain <KiiUser> based on the information parsed from push message.
 
 The payloads can contain the subscribed bucket/topic informations including the scope. This API provides convenience methods to obtain <KiiUser> if the payload contains user scoped bucket/topic information.
 
 @return <KiiUser> instance when the subscribed bucket/topic is user scope. In other cases returns nil.
 @deprecated Use <KiiReceivedMessage>
 */
-(nullable KiiUser*) eventSourceUser __attribute__ ((deprecated));

/**Obtain <KiiThing> based on the information parsed from push message.
 
 The payloads can contain the subscribed bucket/topic informations including the scope. This API provides convenience methods to obtain <KiiThing> if the payload contains thing scoped bucket/topic information.
 
 @return <KiiThing> instance when the subscribed bucket/topic is thing scope. In other cases returns nil.
 @deprecated Use <KiiReceivedMessage>
 */
-(nullable KiiThing*) eventSourceThing __attribute__ ((deprecated));

/**Obtain <KiiGroup> based on the information parsed from push message scope.
 
 The payloads can contain the subscribed bucket/topic informations including the scope. This API provides convenience methods to obtain <KiiGroup> if the payload contains group scoped bucket/topic information.
 
 @return <KiiGroup> instance when the subscribed bucket/topic is group scope. In other cases returns nil.
 @deprecated Use <KiiReceivedMessage>
 */
-(nullable KiiGroup*) eventSourceGroup __attribute__ ((deprecated));

/**Obtain KiiUser based on the information parsed from push message .
 
 @return <KiiUser> instance when the sender of the message is a <KiiUser>. In other cases returns nil.
 @deprecated Use <KiiReceivedMessage>
 */
-(nullable KiiUser*) senderUser __attribute__ ((deprecated));

/**Obtain <KiiThing> based on the information parsed from push message.
 
 @return <KiiThing> instance when the sender of the message is a <KiiThing>. In other cases returns nil.
 @deprecated Use <KiiReceivedMessage>
 */

-(nullable KiiThing*) senderThing __attribute__ ((deprecated));
/**
 * Checks whether the push message contains <KiiBucket> or not.
 
 @return YES if the push message contains <KiiBucket>, otherwise NO.
 @deprecated Use <KiiReceivedMessage>
 *
 */
-(BOOL) containsKiiBucket __attribute__ ((deprecated));

/**
 * Checks whether the push message contains <KiiObject> or not.
 
 @return YES if the push message contains <KiiObject>, otherwise NO.
 @deprecated Use <KiiReceivedMessage>
 */
-(BOOL) containsKiiObject __attribute__ ((deprecated));

/**
 * Checks whether the push message contains <KiiTopic> or not.
 
 @return YES if the push message contains <KiiTopic>, otherwise NO.
 @deprecated Use <KiiReceivedMessage>
 */
-(BOOL) containsKiiTopic __attribute__ ((deprecated));

/**Obtain scope of the bucket/topic.
 
 @return enumeration of message scope. If not provided, it will return KiiMessageScope_UNKNOWN;
 @deprecated Use <KiiReceivedMessage>
 */
-(KiiMessageScope) messageScope __attribute__ ((deprecated));

/** Constructor method that composes a message for all platform (APNS, FCM, MQTT) and provide common payload data.
 @param commonData Dictionary representation of JSON Object with only one-level of nesting. Is equal to setting <data> property.
 @return A KiiPushMessage instance that is associated to the message data.
 */
+(instancetype) composeMessageWithData:(nullable NSDictionary*) commonData;

/** Set flag of APNS delivery If omit calling this method, APNS delivery is enabled.
 @param enabled If YES message would be delivered via APNS. If NO, the apnsFields will set to nil and this message would not delivered thru APNS.
 */
-(void) setAPNSEnabled:(BOOL) enabled;

/** Set flag of GCM delivery If omit calling this method, GCM delivery is enabled.
 @param enabled If YES message would be delivered via GCM. If NO, the gcmFields will set to nil and this message would not delivered thru GCM.
 */
-(void) setGCMEnabled:(BOOL) enabled;

/** Set flag of MQTT delivery If omit calling this method, MQTT delivery is enabled.
 @param enabled If YES message would be delivered via MQTT. If NO, the mqttFields will set to nil and this message would not delivered thru MQTT.
 */
-(void) setMQTTEnabled:(BOOL) enabled;

NS_ASSUME_NONNULL_END
@end
