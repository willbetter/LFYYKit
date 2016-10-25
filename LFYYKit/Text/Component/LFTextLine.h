//
//  LFTextLine.h

//  Created by guoyaoyuan on 15/3/10.
//  
//
//  This source code is licensed under the MIT-style license found in the
//  LICENSE file in the root directory of this source tree.
//

#import <UIKit/UIKit.h>
#import <CoreText/CoreText.h>
#import "LFTextAttribute.h"

/**
 A text line object wrapped `CTLineRef`, see `LFTextLayout` for more.
 */
@interface LFTextLine : NSObject

+ (instancetype)lineWithCTLine:(CTLineRef)CTLine position:(CGPoint)position vertical:(BOOL)isVertical;

@property (nonatomic, assign) NSUInteger index;     ///< line index
@property (nonatomic, assign) NSUInteger row;       ///< line row
@property (nonatomic, strong) NSArray *verticalRotateRange; ///< Run rotate range Array<Array<LFTextRunGlyphRange>>

@property (nonatomic, readonly) CTLineRef CTLine;   ///< CoreText line
@property (nonatomic, readonly) NSRange range;      ///< string range
@property (nonatomic, readonly) BOOL vertical;      ///< vertical form

@property (nonatomic, readonly) CGRect bounds;      ///< bounds (ascent + descent)
@property (nonatomic, readonly) CGSize size;        ///< bounds.size
@property (nonatomic, readonly) CGFloat width;      ///< bounds.size.width
@property (nonatomic, readonly) CGFloat height;     ///< bounds.size.height
@property (nonatomic, readonly) CGFloat top;        ///< bounds.origin.y
@property (nonatomic, readonly) CGFloat bottom;     ///< bounds.origin.y + bounds.size.height
@property (nonatomic, readonly) CGFloat left;       ///< bounds.origin.x
@property (nonatomic, readonly) CGFloat right;      ///< bounds.origin.x + bounds.size.width

@property (nonatomic, assign)   CGPoint position;   ///< baseline position
@property (nonatomic, readonly) CGFloat ascent;     ///< line ascent
@property (nonatomic, readonly) CGFloat descent;    ///< line descent
@property (nonatomic, readonly) CGFloat leading;    ///< line leading
@property (nonatomic, readonly) CGFloat lineWidth;  ///< line width
@property (nonatomic, readonly) CGFloat trailingWhitespaceWidth;

@property (nonatomic, readonly) NSArray *attachments;      ///< LFTextAttachment
@property (nonatomic, readonly) NSArray *attachmentRanges; ///< NSRange(NSValue)
@property (nonatomic, readonly) NSArray *attachmentRects;  ///< CGRect(NSValue)

@end


typedef NS_ENUM(NSUInteger, LFTextRunGlyphDrawMode) {
    /// No rotate.
    LFTextRunGlyphDrawModeHorizontal = 0,
    
    /// Rotate vertical for single glyph.
    LFTextRunGlyphDrawModeVerticalRotate = 1,
    
    /// Rotate vertical for single glyph, and move the glyph to a better position,
    /// such as fullwidth punctuation.
    LFTextRunGlyphDrawModeVerticalRotateMove = 2,
};

/**
 A range in CTRun, used for vertical form.
 */
@interface LFTextRunGlyphRange : NSObject
@property (nonatomic, assign) NSRange glyphRangeInRun;
@property (nonatomic, assign) LFTextRunGlyphDrawMode drawMode;
+ (instancetype)rangeWithRange:(NSRange)range drawMode:(LFTextRunGlyphDrawMode)mode;
@end


