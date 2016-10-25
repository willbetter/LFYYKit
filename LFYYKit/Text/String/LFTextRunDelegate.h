//
//  LFTextRunDelegate.h

//  Created by guoyaoyuan on 14/10/14.
//  
//
//  This source code is licensed under the MIT-style license found in the
//  LICENSE file in the root directory of this source tree.
//

#import <UIKit/UIKit.h>
#import <CoreText/CoreText.h>

/**
 Wrapper for CTRunDelegateRef.
 
 Example:
 
     LFTextRunDelegate *delegate = [LFTextRunDelegate new];
     delegate.ascent = 20;
     delegate.descent = 4;
     delegate.width = 20;
     CTRunDelegateRef ctRunDelegate = delegate.CTRunDelegate;
     if (ctRunDelegate) {
         /// add to attributed string
         CFRelease(ctRunDelegate);
     }
 
 */
@interface LFTextRunDelegate : NSObject <NSCopying, NSCoding>

/**
 Creates and returns the CTRunDelegate.
 
 @discussion You need call CFRelease() after used.
 The CTRunDelegateRef has a strong reference to this LFTextRunDelegate object.
 In CoreText, use CTRunDelegateGetRefCon() to get this LFTextRunDelegate object.
 
 @return The CTRunDelegate object.
 */
- (CTRunDelegateRef)CTRunDelegate CF_RETURNS_RETAINED;

/**
 Additional information about the the run delegate.
 */
@property (nonatomic, strong) NSDictionary *userInfo;

/**
 The typographic ascent of glyphs in the run.
 */
@property (nonatomic, assign) CGFloat ascent;

/**
 The typographic descent of glyphs in the run.
 */
@property (nonatomic, assign) CGFloat descent;

/**
 The typographic width of glyphs in the run.
 */
@property (nonatomic, assign) CGFloat width;

@end
