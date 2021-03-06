//
//  UIPasteboard+LFText.h

//  Created by guoyaoyuan on 15/4/2.
//  
//
//  This source code is licensed under the MIT-style license found in the
//  LICENSE file in the root directory of this source tree.
//

#import <UIKit/UIKit.h>

/**
 Extend UIPasteboard to support image and attributed string.
 */
@interface UIPasteboard (LFText)

@property (nonatomic, copy) NSData *PNGData;    ///< PNG file data
@property (nonatomic, copy) NSData *JPEGData;   ///< JPEG file data
@property (nonatomic, copy) NSData *GIFData;    ///< GIF file data
@property (nonatomic, copy) NSData *WEBPData;   ///< WebP file data
@property (nonatomic, copy) NSData *imageData;  ///< image file data

/// Attributed string,
/// Set this attributed will also set the string property which is copy from the attributed string.
/// If the attributed string contains one or more image, it will also set the `images` property.
@property (nonatomic, copy) NSAttributedString *attributedString;

@end


/// The name identifying the attributed string in pasteboard.
UIKIT_EXTERN NSString *const LFPasteboardTypeAttributedString;

/// The UTI Type identifying WebP data in pasteboard.
UIKIT_EXTERN NSString *const LFUTTypeWEBP;
