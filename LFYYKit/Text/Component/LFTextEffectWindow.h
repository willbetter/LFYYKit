//
//  LFTextEffectWindow.h

//  Created by guoyaoyuan on 15/2/25.
//  
//
//  This source code is licensed under the MIT-style license found in the
//  LICENSE file in the root directory of this source tree.
//

#import <UIKit/UIKit.h>
#import "LFTextMagnifier.h"
#import "LFTextSelectionView.h"

/**
 A window to display magnifier and extra contents for text view.
 
 @discussion Use `sharedWindow` to get the instance, don't create your own instance.
 Typically, you should not use this class directly.
 */
@interface LFTextEffectWindow : UIWindow

/// Returns the shared instance.
+ (instancetype)sharedWindow;

/// Show the magnifier in this window with a 'popup' animation. @param mag A magnifier.
- (void)showMagnifier:(LFTextMagnifier *)mag;
/// Update the magnifier content and position. @param mag A magnifier.
- (void)moveMagnifier:(LFTextMagnifier *)mag;
/// Remove the magnifier from this window with a 'shrink' animation. @param mag A magnifier.
- (void)hideMagnifier:(LFTextMagnifier *)mag;


/// Show the selection dot in this window if the dot is clipped by the selection view.
/// @param selection A selection view.
- (void)showSelectionDot:(LFTextSelectionView *)selection;
/// Remove the selection dot from this window.
/// @param selection A selection view.
- (void)hideSelectionDot:(LFTextSelectionView *)selection;

@end
