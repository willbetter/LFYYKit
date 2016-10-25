//
//  LFGestureRecognizer.h
//
//  Created by guoyaoyuan on 14/10/26.
//   All rights reserved.
//

#import <UIKit/UIKit.h>

/// State of the gesture
typedef NS_ENUM(NSUInteger, LFGestureRecognizerState) {
    LFGestureRecognizerStateBegan, ///< gesture start
    LFGestureRecognizerStateMoved, ///< gesture moved
    LFGestureRecognizerStateEnded, ///< gesture end
    LFGestureRecognizerStateCancelled, ///< gesture cancel
};

/**
 A simple UIGestureRecognizer subclass for recieve touch events.
 */
@interface LFGestureRecognizer : UIGestureRecognizer

@property (nonatomic, readonly) CGPoint startPoint; ///< start point
@property (nonatomic, readonly) CGPoint lastPoint; ///< last move point.
@property (nonatomic, readonly) CGPoint currentPoint; ///< current move point.

/// The action block invoked by every gesture event.
@property (nonatomic, copy) void (^action)(LFGestureRecognizer *gesture, LFGestureRecognizerState state);

/// Cancel the gesture for current touch.
- (void)cancel;

@end
