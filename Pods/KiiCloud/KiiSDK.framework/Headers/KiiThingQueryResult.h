//
//  KiiThingQueryResult.h
//  KiiSDK
//
//  Created by syahRiza on 2017/02/14.
//  Copyright © 2017 Kii Corporation. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "KiiThing.h"


@class KiiThingQuery;
/**
 Class to represent result of KiiThingQuery execution.
 This Class should not be instantiated programatically.
 */
@interface KiiThingQueryResult : NSObject

/** When there are many result of query or data in result is large,
 Query result would be divided into several pages. 
 It returns YES if there are pending result of the Query to be retrieved, NO otherwise.
 */
@property (nonatomic, readonly) BOOL hasNext;

/** Get the array of KiiThing that matches the query. Nil if there is no result;
 */
@property (nonatomic, readonly, nullable) NSArray <KiiThing *> * results;

/** Return KiiThingQuery to get next page of the query. Nil when this result is the last part of the query.
 */
@property (nonatomic, readonly, nullable) KiiThingQuery * nextThingQuery;

/**Synchronously fetch the query result of next page and update array of data can get by <[KiiThingQueryResult results]>
 same as calling <[KiiThing querySynchronous:]> with the query get by <nextKiiThingQuery>

 This is a blocking methods.

 @param error used to return an error by reference (pass NULL if this is not desired). It is recommended to set an actual error object to get the error information.
 @return Thing query result.
 */
- (KiiThingQueryResult * _Nullable) getNextResultSynchronous:(NSError*_Nullable*_Nullable)error;

/**Asynchronously fetch the query result of next page and update array of data can get by <[KiiThingQueryResult results]>
 same as calling <[KiiThing querySynchronous:]> with the query get by <nextKiiThingQuery>.
 This method is a non-blocking version of <getNextResultSynchronous:>

    [aThingQueryResult getNextResult:^(KiiThingQueryResult *queryResult, NSError *error){
         //print the executed query
         if(error == nil) {
             NSLog(@"Got Results: %@", queryResult.results);
             NSLog(@"Total result %@", queryResult.results.count);
             NSLog(@"Has Next: %@ next", queryResult.hasNext?@"Yes":@"No");
         }
     }];
     
 @param block The block to be called upon method completion. See example.
 */
- (void) getNextResult:(KiiThingQueryResultBlock _Nonnull) block;


@end
