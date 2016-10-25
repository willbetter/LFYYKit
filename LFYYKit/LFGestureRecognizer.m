//
//  LFGestureRecognizer.m
//
//  Created by guoyaoyuan on 14/10/26.
//   All rights reserved.
//

#import "LFGestureRecognizer.h"
#import <UIKit/UIGestureRecognizerSubclass.h>

@implementation LFGestureRecognizer

- (void)touchesBegan:(NSSet *)touches withEvent:(UIEvent *)event {
    self.state = UIGestureRecognizerStateBegan;
    _startPoint = [(UITouch *)[touches anyObject] locationInView : self.view];
    _lastPoint = _currentPoint;
    _currentPoint = _startPoint;
    if (_action) _action(self, LFGestureRecognizerStateBegan);
}

- (void)touchesMoved:(NSSet *)touches withEvent:(UIEvent *)event {
    UITouch *touch = (UITouch *)[touches anyObject];
    CGPoint currentPoint = [touch locationInView:self.view];
    self.state = UIGestureRecognizerStateChanged;
    _currentPoint = currentPoint;
    if (_action) _action(self, LFGestureRecognizerStateMoved);
    _lastPoint = _currentPoint;
}

- (void)touchesEnded:(NSSet *)touches withEvent:(UIEvent *)event {
    self.state = UIGestureRecognizerStateEnded;
    if (_action) _action(self, LFGestureRecognizerStateEnded);
}

- (void)touchesCancelled:(NSSet *)touches withEvent:(UIEvent *)event {
    self.state = UIGestureRecognizerStateCancelled;
    if (_action) _action(self, LFGestureRecognizerStateCancelled);
}

- (void)reset {
    self.state = UIGestureRecognizerStatePossible;
}

- (void)cancel {
    if (self.state == UIGestureRecognizerStateBegan || self.state == UIGestureRecognizerStateChanged) {
        self.state = UIGestureRecognizerStateCancelled;
        if (_action) _action(self, LFGestureRecognizerStateCancelled);
    }
}

@end
