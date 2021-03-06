/*
 *  CMStepCounter.h
 *  CoreMotion
 *
 *  Copyright (c) 2013 Apple Inc. All rights reserved.
 *
 */

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

/*
 *  CMStepQueryHandler
 *
 *  Discussion:
 *    Typedef of block to be invoked when the step count query is completed.
 */
//查询历史数据处理块
typedef void (^CMStepQueryHandler)(NSInteger numberOfSteps, NSError * __nullable error) __TVOS_PROHIBITED __WATCHOS_PROHIBITED;

/*
 *  CMStepUpdateHandler
 *
 *  Discussion:
 *      Typedef of block to be invoked on every update.  The total step count since startStepCountingUpdatesToQueue
 *      was called along with the timestamp associated with the latest determination will be returned.
 */
//步数更新处理块
typedef void (^CMStepUpdateHandler)(NSInteger numberOfSteps, NSDate *timestamp, NSError * __nullable error) __TVOS_PROHIBITED __WATCHOS_PROHIBITED;

/*
 *  CMStepCounter
 *
 *  Discussion:
 *      CMStepCounter allows access to the approximate number of steps a user has taken
 *      with a device.  Steps can be retrieved in one of two ways:
 *
 *      1. Via a query specifying a time range from which the approximate number of steps is
 *      tabulated and returned. (See queryStepCountStartingFrom:to:toQueue:withHandler)
 *
 *      2. By providing a queue and a block to startStepCountingUpdatesToQueue:withHandler,
 *      step count updates will be provided on a best effort basis.  Each update will return a
 *      monotonically increasing number of steps counted since
 *      startStepCountingUpdatesToQueue:withHandler was called and a timestamp
 *      associated with the latest stepcount determination.  Step count updates can be stopped
 *      by either calling stopStepCountingUpdates or upon CMStepCounter deallocation.
 *
 */
 // 7+添加的计步器,但8+后使用CMPedometer替代
NS_CLASS_DEPRECATED_IOS(7_0,8_0,"Use CMPedometer instead") __TVOS_PROHIBITED __WATCHOS_PROHIBITED
@interface CMStepCounter : NSObject

/*
 *  isStepCountingAvailable
 *
 *  Discussion:
 *      Determines whether the device supports step counting.
 */
//计步器功能是否可用
+ (BOOL)isStepCountingAvailable;

/*
 *  queryStepCountStartingFrom:to:toQueue:withHandler
 *
 *  Discussion:
 *      Queries for the approximate number of steps taken in the given time range, for up to 7 days.
 *      The step count returned is computed from a system wide history that is continuously being
 *      collected in the background.  The result is returned to the handler/queue specified.
 */
// 查询历史数据
- (void)queryStepCountStartingFrom:(NSDate *)start
                                to:(NSDate *)end
                           toQueue:(NSOperationQueue *)queue
                       withHandler:(CMStepQueryHandler)handler;

/*
 *  startStepCountingUpdatesToQueue:withHandler
 *
 *  Discussion:
 *       Starts a series of continuous step counting updates to the handler on the designated queue.  For each
 *       update, the app will receive the total step count since this method was called (this includes
 *       subsequent calls) and the timestamp associated with the latest determination.  If the app is backgrounded
 *       and resumed at a later time, the app will receive all of the steps counted during the background
 *       period in the very next update.  The handler will be called when the number of steps (as defined by
 *       the user) has been detected on a best effort basis.
 */
// 每隔stepCounts在queue中执行一次handler 
- (void)startStepCountingUpdatesToQueue:(NSOperationQueue *)queue
                               updateOn:(NSInteger)stepCounts
                            withHandler:(CMStepUpdateHandler)handler;


/*
 *  stopStepCountingUpdates
 *
 *  Discussion:
 *      Stops step counting updates.  Upon deallocation of CMStepCounter, this function will be
 *      automatically invoked if updates are still active and stopStepCountingUpdates has not been
 *      called.
 */
//停止计步数据更新 
- (void)stopStepCountingUpdates;

@end

NS_ASSUME_NONNULL_END
