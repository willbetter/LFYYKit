//
//  NSParagraphStyle+LFText.h

//  Created by guoyaoyuan on 14/10/7.
//  
//
//  This source code is licensed under the MIT-style license found in the
//  LICENSE file in the root directory of this source tree.
//

#import <UIKit/UIKit.h>

/**
 Provides extensions for `NSParagraphStyle` to work with CoreText.
 */
@interface NSParagraphStyle (LFAdd)

/**
 Creates a new NSParagraphStyle object from the CoreText Style.
 
 @param CTStyle CoreText Paragraph Style.
 
 @return a new NSParagraphStyle
 */
+ (NSParagraphStyle *)styleWithCTStyle:(CTParagraphStyleRef)CTStyle;

/**
 Creates and returns a CoreText Paragraph Style. (need call CFRelease() after used)
 */
- (CTParagraphStyleRef)CTStyle CF_RETURNS_RETAINED;

@end
