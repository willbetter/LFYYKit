//
//  LFTextKeyboardManager.h

//  Created by guoyaoyuan on 15/6/3.
//  
//
//  This source code is licensed under the MIT-style license found in the
//  LICENSE file in the root directory of this source tree.
//

#import <UIKit/UIKit.h>

/**
 System keyboard transition information.
 Use -[LFTextKeyboardManager convertRect:toView:] to convert frame to specified view.
 */
typedef struct {
    BOOL fromVisible; ///< Keyboard visible before transition.
    BOOL toVisible;   ///< Keyboard visible after transition.
    CGRect fromFrame; ///< Keyboard frame before transition.
    CGRect toFrame;   ///< Keyboard frame after transition.
    NSTimeInterval animationDuration;       ///< Keyboard transition animation duration.
    UIViewAnimationCurve animationCurve;    ///< Keyboard transition animation curve.
    UIViewAnimationOptions animationOption; ///< Keybaord transition animation option.
} LFTextKeyboardTransition;


/**
 The LFTextKeyboardObserver protocol defines the method you can use
 to receive system keyboard change information.
 */
@protocol LFTextKeyboardObserver <NSObject>
@optional
- (void)keyboardChangedWithTransition:(LFTextKeyboardTransition)transition;
@end


/**
 A LFTextKeyboardManager object lets you get the system keyboard information,
 and track the keyboard visible/frame/transition.
 
 @discussion You should access this class in main thread.
 Compatible: iPhone/iPad with iOS6/7/8/9.
 */
@interface LFTextKeyboardManager : NSObject

/// Get the default manager.
+ (instancetype)defaultManager;

/// Get the keyboard window. nil if there's no keyboard window.
@property (nonatomic, readonly) UIWindow *keyboardWindow;

/// Get the keyboard view. nil if there's no keyboard view.
@property (nonatomic, readonly) UIView *keyboardView;

/// Whether the keyboard is visible.
@property (nonatomic, readonly, getter=isKeyboardVisible) BOOL keyboardVisible;

/// Get the keyboard frame. CGRectNull if there's no keyboard view.
/// Use convertRect:toView: to convert frame to specified view.
@property (nonatomic, readonly) CGRect keyboardFrame;


/**
 Add an observer to manager to get keyboard change information.
 This method makes a weak reference to the observer.
 
 @param observer An observer. 
 This method will do nothing if the observer is nil, or already added.
 */
- (void)addObserver:(id<LFTextKeyboardObserver>)observer;

/**
 Remove an observer from manager.
 
 @param observer An observer.
 This method will do nothing if the observer is nil, or not in manager.
 */
- (void)removeObserver:(id<LFTextKeyboardObserver>)observer;

/**
 Convert rect to specified view or window.
 
 @param rect The frame rect.
 @param view A specified view or window (pass nil to convert for main window).
 @return The converted rect in specifeid view.
 */
- (CGRect)convertRect:(CGRect)rect toView:(UIView *)view;

@end
