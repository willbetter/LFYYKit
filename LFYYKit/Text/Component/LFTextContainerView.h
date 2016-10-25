//
//  LFTextContainerView.h

//  Created by guoyaoyuan on 15/4/21.
//  
//
//  This source code is licensed under the MIT-style license found in the
//  LICENSE file in the root directory of this source tree.
//

#import <UIKit/UIKit.h>
#import "LFTextLayout.h"

/**
 A simple view to diaplay `LFTextLayout`.

 @discussion This view can become first responder. If this view is first responder,
 all the action (such as UIMenu's action) would forward to the `hostView` property.
 Typically, you should not use this class directly.
 
 @warning All the methods in this class should be called on main thread.
 */
@interface LFTextContainerView : UIView

/// First responder's aciton will forward to this view.
@property (nonatomic, weak) UIView *hostView;

/// Debug option for layout debug. Set this property will let the view redraw it's contents.
@property (nonatomic, copy) LFTextDebugOption *debugOption;

/// Text vertical alignment.
@property (nonatomic, assign) LFTextVerticalAlignment textVerticalAlignment;

/// Text layout. Set this property will let the view redraw it's contents.
@property (nonatomic, strong) LFTextLayout *layout;

/// The contents fade animation duration when the layout's contents changed. Default is 0 (no animation).
@property (nonatomic, assign) NSTimeInterval contentsFadeDuration;

/// Convenience method to set `layout` and `contentsFadeDuration`.
/// @param layout  Same as `layout` property.
/// @param fadeDuration  Same as `contentsFadeDuration` property.
- (void)setLayout:(LFTextLayout *)layout withFadeDuration:(NSTimeInterval)fadeDuration;

@end
