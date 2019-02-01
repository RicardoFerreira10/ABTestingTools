//
//  KiiReceivedMessage.h
//  KiiSDK
//
//  Created by syahRiza on 2016/11/29.
//  Copyright © 2016 Kii Corporation. All rights reserved.
//

#import <Foundation/Foundation.h>

/** Enumeration of KiiMessageScope that represents KiiPushMessage Object/Topic Scope.
 */
typedef NS_ENUM(NSInteger, KiiMessageScope) {

    /** Scope is not provided */
    KiiMessageScope_UNKNOWN = -1,
    /** App Scope */
    KiiMessageScope_APP,
    /** Group Scope */
    KiiMessageScope_APP_AND_GROUP,
    /** User Scope */
    KiiMessageScope_APP_AND_USER,
    /** Thing Scope */
    KiiMessageScope_APP_AND_THING,
};

/** Enumeration of KiiMessageField that represents KiiCloud specific fields.

 KiiMessageField list is as follows:

 Key           | Short key | Push to App | Push to User                        | Direct Push                           | Description                                          | Possible values
 ---------------|-----------|-------------|-------------------------------------|---------------------------------------|------------------------------------------------------|------
 KiiMessage_APP_ID         | a         | -           | -<br>(Depends on "sendAppID")       | -                                     | Source app which generated the notification.         |
 KiiMessage_SENDER         | s         | -           | X<br>(Depends on "sendSender")      | X<br>(Depends on "sendSender")        | The user or thing who caused the notification.                |
 KiiMessage_ORIGIN         | o         | -           | -<br>(Depends on "sendOrigin")      | -<br>(Depends on "sendOrigin")        | Origin of push. "EVENT" for "Push to App" notification. "EXPLICIT" for "Push to User" and "Direct Push" notification. | - EVENT<br> - EXPLICIT
 KiiMessage_WHEN           | w         | X           | -<br>(Depends on "sendWhen")        | -<br>(Depends on "sendWhen")          | The timestamp of the notification in milliseconds. (Since January 1, 1970 00:00:00 UTC) |
 KiiMessage_TYPE           | t         | X           | -<br>(Depends on "pushMessageType") | -<br>(Depends on "pushMessageType")   | The type of notification and the additional data.    | [Push to App]<br>- DATA_OBJECT_CREATED<br> - DATA_OBJECT_DELETED<br> - DATA_OBJECT_UPDATED<br> - DATA_OBJECT_BODY_UPDATED<br> - DATA_OBJECT_BODY_DELETED<br> - DATA_OBJECT_ACL_MODIFIED<br> - BUCKET_DELETED
 KiiMessage_TOPIC          | to        | -           | X<br>(Depends on "sendTopicID")     | -                                     | TopicID that is the source of this notification. TopicID is only for "Push to User" push messages.    |
 KiiMessage_SCOPE_APP_ID   | sa        | X           | X<br>(Depends on "sendObjectScope") | -                                     | AppID of topic/object scope.                               |
 KiiMessage_SCOPE_USER_ID  | su        | X           | X<br>(Depends on "sendObjectScope") | -                                     | UserID of topic/topic/object scope. Push message has this field only if the subscribed bucket/topic is user scope.|
 KiiMessage_SCOPE_GROUP_ID | sg        | X           | X<br>(Depends on "sendObjectScope") | -                                     | GroupID of topic/object scope. Push message has this field only if the subscribed bucket/topic is group scope. |
 KiiMessage_SCOPE_THING_ID | sth        | X           | X<br>(Depends on "sendObjectScope") | -                                     | ThingID of topic/object scope. Push message has this field only if the subscribed bucket/topic is thing scope. |
 KiiMessage_SCOPE_TYPE     | st        | X           | X<br>(Depends on "sendObjectScope") | -                                     | Type of topic/object scope.                                 | - APP<br> - APP_AND_USER<br> - APP_AND_GROUP<br> - APP_AND_THING
 KiiMessage_BUCKET_ID      | bi        | X           | -                                   | -                                     | Bucket name of push subscribed.                      |
 KiiMessage_BUCKET_TYPE    | bt        | X           | -                                   | -                                     | Type of source bucket.                    | - rw<br> - sync
 KiiMessage_OBJECT_ID      | oi        | X           | -                                   | -                                     | ID of the object operated.                           |
 KiiMessage_OBJECT_MODIFIED_AT | om    | -           | -                                   | -                                     | Timestamp of the modification of object in milliseconds. (Since January 1, 1970 00:00:00 UTC)  | - DATA_OBJECT_CREATED<br> - DATA_OBJECT_UPDATED<br> - DATA_OBJECT_BODY_UPDATE

 */
typedef NS_ENUM(NSUInteger, KiiMessageField) {
    /** Source app which generated the notification. */
    KiiMessage_APP_ID,
    /** The user who caused the notification. */
    KiiMessage_SENDER,
    /** The type of notification and the additional data. */
    KiiMessage_TYPE,
    /** The timestamp of the notification in milliseconds.
     (Since January 1, 1970 00:00:00 UTC) */
    KiiMessage_WHEN,
    /** Origin of push. "EVENT" for "Push to App" notification.
     "EXPLICIT" for "Push to User" and "Direct Push" notification. */
    KiiMessage_ORIGIN,
    /** TopicID that is the source of this notification.
     TopicID is only for "Push to User" push messages. */
    KiiMessage_TOPIC,
    /** AppID of topic/object scope. */
    KiiMessage_SCOPE_APP_ID,
    /** UserID of topic/object scope.
     Push message has this field only if the subscribed bucket/topic is user scope. */
    KiiMessage_SCOPE_USER_ID,
    /** GroupID of topic/object scope.
     Push message has this field only if the subscribed bucket/topic is group scope. */
    KiiMessage_SCOPE_GROUP_ID,
    /** Type of topic/object scope. */
    KiiMessage_SCOPE_TYPE,
    /** Bucket name of push subscribed. */
    KiiMessage_BUCKET_ID,
    /** Type of source bucket. */
    KiiMessage_BUCKET_TYPE,
    /** ID of the object operated. */
    KiiMessage_OBJECT_ID,
    /** Timestamp of the modification of object in milliseconds.
     (Since January 1, 1970 00:00:00 UTC) */
    KiiMessage_OBJECT_MODIFIED_AT,
    /** ThingID of topic/object scope.
     Push message has this field only if the subscribed bucket/topic is thing scope. */
    KiiMessage_SCOPE_THING_ID
};

@class KiiAPNSFields,KiiGCMFields,KiiMQTTFields,KiiBucket,KiiObject,KiiTopic,KiiUser,KiiThing,KiiGroup;

/**
 Class for encapsulating incoming push notification message
 Three types of push message supported by KiiCloud.

 - **Push to App** : Message sent to the subscribers when an event happens in the <KiiBucket>.
 - **Push to User** : Message sent to the subscribers of <KiiTopic> that is created explicitly.
 - **Direct Push** : Message sent to a certain user by manipulating the developer portal. (Only app developer can send this message.)

 Following section describes the contents of "Push to App", "Push to User" and "Direct Push" message.

 ### Contents of Push Message

 Push message of "Push to App", "Push to User" and "Direct Push" contains the KiiCloud specific fields that are selected by the message sender.
 And also push message of "Push to User" contains the basic message as key-value pair that is sent to the <KiiTopic>.

 KiiCloud specific fields are as follows:

 Key           | Short key | Push to App | Push to User                        | Direct Push                           | Description                                          | Possible values
 ---------------|-----------|-------------|-------------------------------------|---------------------------------------|------------------------------------------------------|------
 KiiMessage_APP_ID         | a         | -           | -<br>(Depends on "sendAppID")       | -                                     | Source app which generated the notification.         |
 KiiMessage_SENDER         | s         | -           | X<br>(Depends on "sendSender")      | X<br>(Depends on "sendSender")        | The user or thing who caused the notification.                |
 KiiMessage_ORIGIN         | o         | -           | -<br>(Depends on "sendOrigin")      | -<br>(Depends on "sendOrigin")        | Origin of push. "EVENT" for "Push to App" notification. "EXPLICIT" for "Push to User" notification. | - EVENT<br> - EXPLICIT
 KiiMessage_WHEN           | w         | X           | -<br>(Depends on "sendWhen")        | -<br>(Depends on "sendWhen")          | The timestamp of the notification in milliseconds. (Since January 1, 1970 00:00:00 UTC) |
 KiiMessage_TYPE           | t         | X           | -<br>(Depends on "pushMessageType") | -<br>(Depends on "pushMessageType")   | The type of notification and the additional data.    | [Push to App]<br>- DATA_OBJECT_CREATED<br> - DATA_OBJECT_DELETED<br> - DATA_OBJECT_UPDATED<br> - DATA_OBJECT_BODY_UPDATED<br> - DATA_OBJECT_BODY_DELETED<br> - DATA_OBJECT_ACL_MODIFIED<br> - BUCKET_DELETED
 KiiMessage_TOPIC          | to        | -           | X<br>(Depends on "sendTopicID")     | -                                     | TopicID is only for "Push to User" push messages.    |
 KiiMessage_SCOPE_APP_ID   | sa        | X           | X<br>(Depends on "sendObjectScope") | -                                     | AppID of topic/object scope.                               |
 KiiMessage_SCOPE_USER_ID  | su        | X           | X<br>(Depends on "sendObjectScope") | -                                     | UserID of topic/object scope. Push message has this field only if the subscribed bucket/topic is user scope.|
 KiiMessage_SCOPE_GROUP_ID | sg        | X           | X<br>(Depends on "sendObjectScope") | -                                     | GroupID of topic/object scope. Push message has this field only if the subscribed bucket/topic is group scope. |
 KiiMessage_SCOPE_THING_ID | sth        | X           | X<br>(Depends on "sendObjectScope") | -                                     | ThingID of topic/object scope. Push message has this field only if the subscribed bucket/topic is thing scope. |
 KiiMessage_SCOPE_TYPE     | st        | X           | X<br>(Depends on "sendObjectScope") | -                                     | Type of topic/object scope.                                 | - APP<br> - APP_AND_USER<br> - APP_AND_GROUP<br> - APP_AND_THING
 KiiMessage_BUCKET_ID      | bi        | X           | -                                   | -                                     | Bucket name of push subscribed.                      |
 KiiMessage_BUCKET_TYPE    | bt        | X           | -                                   | -                                     | Type of bucket has been modified.                    | - rw<br> - sync
 KiiMessage_OBJECT_ID      | oi        | X           | -                                   | -                                     | ID of the object operated.                           |
 KiiMessage_OBJECT_MODIFIED_AT | om    | -           | -                                   | -                                     | Timestamp of the modification of object in milliseconds. (Since January 1, 1970 00:00:00 UTC)  | - DATA_OBJECT_CREATED<br> - DATA_OBJECT_UPDATED<br> - DATA_OBJECT_BODY_UPDATE
 */
@interface KiiReceivedMessage : NSObject
NS_ASSUME_NONNULL_BEGIN

/** Dictionary representation of APNs received message.
 */
@property(nonatomic,readonly,nullable) NSDictionary* rawMessage;

/** Parse incoming APNs message.
 @param userInfo An userInfo instance that received from APNs as a push message.
 @return A KiiPushMessage instance that is associated to the userInfo.
 */
+ (instancetype)messageFromAPNS:(NSDictionary *)userInfo;

/** Get specific value of received message meta data.
 @param field Enumeration of <KiiMessageField>.
 @return A NSString object that is associated to the message fields.
 */
-(nullable NSString*) getValueOfKiiMessageField:(KiiMessageField) field;

/** Get alert body's text message.
 @return A NSString object of alert body text message.
 */
-(nullable NSString*) getAlertBody;

/** Show simple alert to display alert body's message.
 @param title A alert title to display.
 */
-(void) showMessageAlertWithTitle:(nullable NSString*) title;

/**Obtain <KiiBucket> based on the information parsed from push message.

 The payloads can contain the subscribed bucket informations including the scope and the type (encrypted or not). This API provides convenience methods to obtain <KiiBucket> if the payload contains the subscribed bucket information.

 @return <KiiBucket> instance when the event of KiiBucket or <KiiObject> inside <KiiBucket> happened. In other cases returns nil.
 */
-(nullable KiiBucket*) eventSourceBucket;

/**Obtain <KiiObject> based on the information parsed from push message.

 The payloads can contain the subscribed bucket's object informations including the scope. This API provides convenience methods to obtain <KiiObject> if the payload contains the object information.

 @return <KiiObject> instance when the event of <KiiObject>
 * inside <KiiBucket> happened. In other cases returns nil.
 */
-(nullable KiiObject*) eventSourceObject;

/**Obtain <KiiTopic> based on the information parsed from push message.

 The payloads can contain the subscribed topic informations including the scope. This API provides convenience methods to obtain <KiiTopic>  if the payload contains the subscribed topic information.

 @return <KiiTopic> instance when the event of KiiTopic (Push to User). In other cases returns nil.
 */
-(nullable KiiTopic*) eventSourceTopic;

/**Obtain <KiiUser> based on the information parsed from push message.

 The payloads can contain the subscribed bucket/topic informations including the scope. This API provides convenience methods to obtain <KiiUser> if the payload contains user scoped bucket/topic information.

 @return <KiiUser> instance when the subscribed bucket/topic is user scope. In other cases returns nil.
 */
-(nullable KiiUser*) eventSourceUser;

/**Obtain <KiiThing> based on the information parsed from push message.

 The payloads can contain the subscribed bucket/topic informations including the scope. This API provides convenience methods to obtain <KiiThing> if the payload contains thing scoped bucket/topic information.

 @return <KiiThing> instance when the subscribed bucket/topic is thing scope. In other cases returns nil.
 */
-(nullable KiiThing*) eventSourceThing;

/**Obtain <KiiGroup> based on the information parsed from push message scope.

 The payloads can contain the subscribed bucket/topic informations including the scope. This API provides convenience methods to obtain <KiiGroup> if the payload contains group scoped bucket/topic information.

 @return <KiiGroup> instance when the subscribed bucket/topic is group scope. In other cases returns nil.
 */
-(nullable KiiGroup*) eventSourceGroup;

/**Obtain KiiUser based on the information parsed from push message .

 @return <KiiUser> instance when the sender of the message is a <KiiUser>. In other cases returns nil.
 */
-(nullable KiiUser*) senderUser;

/**Obtain <KiiThing> based on the information parsed from push message.

 @return <KiiThing> instance when the sender of the message is a <KiiThing>. In other cases returns nil.
 */

-(nullable KiiThing*) senderThing;
/**
 * Checks whether the push message contains <KiiBucket> or not.

 @return YES if the push message contains <KiiBucket>, otherwise NO.
 *
 */
-(BOOL) containsKiiBucket;

/**
 * Checks whether the push message contains <KiiObject> or not.

 @return YES if the push message contains <KiiObject>, otherwise NO.
 */
-(BOOL) containsKiiObject;

/**
 * Checks whether the push message contains <KiiTopic> or not.

 @return YES if the push message contains <KiiTopic>, otherwise NO.
 */
-(BOOL) containsKiiTopic;

/**Obtain scope of the bucket/topic.

 @return enumeration of message scope. If not provided, it will return KiiMessageScope_UNKNOWN;
 */
-(KiiMessageScope) messageScope;
NS_ASSUME_NONNULL_END
@end
