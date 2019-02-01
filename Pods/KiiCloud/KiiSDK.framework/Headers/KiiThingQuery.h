//
//  KiiThingQuery.h
//  KiiSDK
//
//  Created by syahRiza on 2017/02/14.
//  Copyright © 2017 Kii Corporation. All rights reserved.
//

#import <Foundation/Foundation.h>
@class KiiThingQueryResult;
@class KiiThing;
@class KiiUser;
@class KiiGroup;
/** A class that is representation of Thing Query object. This class should be instantiated with designated initializer. Calling `init` will throw an exception.
 */
@interface KiiThingQuery : NSObject
/** The thing type to filter the results.
 */
@property (nonatomic,strong,nullable) NSString * thingType;

/** The maximum number of results returned on response. Default is 0 which is no limit will be set into the query and use what is defined by server. This limit behaves in a best effort way, actual number of <br>
 returned result can be smaller than the requested number. If the specified limit is greater than the limit of the server, limit of the server will be applied.
 */
@property (nonatomic, assign) unsigned int limit;

/** Creates a query to search things owned by the specified user and groups.
  Both the owner and groupOwners parameter are optional, but at least one of them must be supplied.
  @param owner <KiiUser> object must be current user.
  @param groupOwners List of groups must be belonged by current user.
  @exception NSInvalidArgumentException if both (owner and groups) are nil.
  @exception NSInvalidArgumentException if groups contains non <KiiGroup> instance.
  @exception NSInvalidArgumentException if groups contains group that does not have groupID.
  @exception NSInvalidArgumentException if the owner is nil and groups is an empty array.
 */
+(instancetype _Nonnull) thingQuery: (KiiUser*  _Nullable) owner groups: ( NSArray <KiiGroup *> * _Nullable) groups;


@end
