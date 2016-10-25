//
//  LFTextMagnifier.h

//  Created by guoyaoyuan on 15/2/25.
//  
//
//  This source code is licensed under the MIT-style license found in the
//  LICENSE file in the root directory of this source tree.
//

#import <UIKit/UIKit.h>
#import "LFTextAttribute.h"

/// Magnifier type
typedef NS_ENUM(NSInteger, LFTextMagnifierType) {
    LFTextMagnifierTypeCaret,  ///< Circular magnifier
    LFTextMagnifierTypeRanged, ///< Round rectangle magnifier
};

/**
 A magnifier view which can be displayed in `LFTextEffectWindow`.
 
 @discussion Use `magnifierWithType:` to create instance.
 Typically, you should not use this class directly.
 */
@interface LFTextMagnifier : UIView

/// Create a mangifier with the specified type. @param type The magnifier type.
+ (id)magnifierWithType:(LFTextMagnifierType)type;

@property (nonatomic, readonly) LFTextMagnifierType type; ///< Type of magnifier
@property (nonatomic, readonly) CGSize fitSize;           ///< The 'best' size for magnifier view.
@property (nonatomic, readonly) CGSize snapshotSize;      ///< The 'best' snapshot image size for magnifier.
@property (nonatomic, strong) UIImage *snapshot;          ///< The image in magnifier (readwrite).

@property (nonatomic, weak) UIView *hostView;             ///< The coordinate based view.
@property (nonatomic, assign) CGPoint hostCaptureCenter;  ///< The snapshot capture center in `hostView`.
@property (nonatomic, assign) CGPoint hostPopoverCenter;  ///< The popover center in `hostView`.
@property (nonatomic, assign) BOOL hostVerticalForm;      ///< The host view is vertical form.
@property (nonatomic, assign) BOOL captureDisabled;       ///< A hint for `LFTextEffectWindow` to disable capture.
@property (nonatomic, assign) BOOL captureFadeAnimation;  ///< Show fade animation when the snapshot image changed.

@end
