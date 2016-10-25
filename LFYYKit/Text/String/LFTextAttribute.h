//
//  LFTextAttribute.h

//  Created by guoyaoyuan on 14/10/26.
//  
//
//  This source code is licensed under the MIT-style license found in the
//  LICENSE file in the root directory of this source tree.
//

#ifndef LFKit_LFText_h
#define LFKit_LFText_h

#import <UIKit/UIKit.h>


#pragma mark - Enum Define

/// The attribute type
typedef NS_OPTIONS(NSInteger, LFTextAttributeType) {
    LFTextAttributeTypeNone     = 0,
    LFTextAttributeTypeUIKit    = 1 << 0, ///< UIKit attributes, such as UILabel/UITextField/drawInRect.
    LFTextAttributeTypeCoreText = 1 << 1, ///< CoreText attributes, used by CoreText.
    LFTextAttributeTypeLFText   = 1 << 2, ///< LFText attributes, used by LFText.
};

/// Get the attribute type from an attribute name.
extern LFTextAttributeType LFTextAttributeGetType(NSString *attributeName);

/**
 Line style in LFText (similar to NSUnderlineStyle).
 */
typedef NS_OPTIONS (NSInteger, LFTextLineStyle) {
    // basic style (bitmask:0xFF)
    LFTextLineStyleNone       = 0x00, ///< (        ) Do not draw a line (Default).
    LFTextLineStyleSingle     = 0x01, ///< (──────) Draw a single line.
    LFTextLineStyleThick      = 0x02, ///< (━━━━━━━) Draw a thick line.
    LFTextLineStyleDouble     = 0x09, ///< (══════) Draw a double line.
    
    // style pattern (bitmask:0xF00)
    LFTextLineStylePatternSolid      = 0x000, ///< (────────) Draw a solid line (Default).
    LFTextLineStylePatternDot        = 0x100, ///< (‑ ‑ ‑ ‑ ‑ ‑) Draw a line of dots.
    LFTextLineStylePatternDash       = 0x200, ///< (— — — —) Draw a line of dashes.
    LFTextLineStylePatternDashDot    = 0x300, ///< (— ‑ — ‑ — ‑) Draw a line of alternating dashes and dots.
    LFTextLineStylePatternDashDotDot = 0x400, ///< (— ‑ ‑ — ‑ ‑) Draw a line of alternating dashes and two dots.
    LFTextLineStylePatternCircleDot  = 0x900, ///< (••••••••••••) Draw a line of small circle dots.
};

/**
 Text vertical alignment.
 */
typedef NS_ENUM(NSInteger, LFTextVerticalAlignment) {
    LFTextVerticalAlignmentTop =    0, ///< Top alignment.
    LFTextVerticalAlignmentCenter = 1, ///< Center alignment.
    LFTextVerticalAlignmentBottom = 2, ///< Bottom alignment.
};

/**
 The direction define in LFText.
 */
typedef NS_OPTIONS(NSUInteger, LFTextDirection) {
    LFTextDirectionNone   = 0,
    LFTextDirectionTop    = 1 << 0,
    LFTextDirectionRight  = 1 << 1,
    LFTextDirectionBottom = 1 << 2,
    LFTextDirectionLeft   = 1 << 3,
};

/**
 The trunction type, tells the truncation engine which type of truncation is being requested.
 */
typedef NS_ENUM (NSUInteger, LFTextTruncationType) {
    /// No truncate.
    LFTextTruncationTypeNone   = 0,
    
    /// Truncate at the beginning of the line, leaving the end portion visible.
    LFTextTruncationTypeStart  = 1,
    
    /// Truncate at the end of the line, leaving the start portion visible.
    LFTextTruncationTypeEnd    = 2,
    
    /// Truncate in the middle of the line, leaving both the start and the end portions visible.
    LFTextTruncationTypeMiddle = 3,
};



#pragma mark - LFText 新增的属性

/// Value 是 LFTextBackedString
/// 当某些文本被替换为其他东西时（例如 [大笑] 被替换为表情符号），可以用该属性存储原始文本。
/// 文本复制时可能会被用到
UIKIT_EXTERN NSString *const LFTextBackedStringAttributeName;

/// Value 是 LFTextBinding
/// 将一段文本绑定起来作为一个整体进行复制和删除。就像短息输入联系人的控件那样。
UIKIT_EXTERN NSString *const LFTextBindingAttributeName;

/// Value 是 LFTextShadow
/// 文本阴影。（可以通过 LFTextShadow.subShadow 来添加多个重叠的阴影）
UIKIT_EXTERN NSString *const LFTextShadowAttributeName;

/// Value 是 LFTextShadow
/// 文本内阴影。（可以通过 LFTextShadow.subShadow 来添加多个重叠的内阴影）
UIKIT_EXTERN NSString *const LFTextInnerShadowAttributeName;

/// Value 是 LFTextDecoration
/// 下划线
UIKIT_EXTERN NSString *const LFTextUnderlineAttributeName;

/// Value 是 LFTextDecoration
/// 删除线
UIKIT_EXTERN NSString *const LFTextStrikethroughAttributeName;

/// Value 是 LFTextBorder
/// 文本边线。就像下面这样。
///
/// ╭─────╮
/// │ Text │
/// ╰─────╯
UIKIT_EXTERN NSString *const LFTextBorderAttributeName;

/// Value 是 LFTextBorder
/// 文本背景边线。就像下面这样。
///
/// ╭─────╮
/// │ Text │
/// ╰─────╯
UIKIT_EXTERN NSString *const LFTextBackgroundBorderAttributeName;

/// Value 是 LFTextBorder
/// 该边线会被绘制到和视图等宽。一般用不到。。
UIKIT_EXTERN NSString *const LFTextBlockBorderAttributeName;

/// value 是 LFTextBorder
/// 文本附件。用于图文混排
/// 该属性应该配合 CTRunDelegate 使用
UIKIT_EXTERN NSString *const LFTextAttachmentAttributeName;

/// Value 是 LFTextHighlight
/// 文本高亮范围，用于链接点击
UIKIT_EXTERN NSString *const LFTextHighlightAttributeName;

/// Value 是 CGAffineTransform(NSValue)
/// 用于控制每个字符的变形
UIKIT_EXTERN NSString *const LFTextGlyphTransformAttributeName;



#pragma mark - 一些预定义字符串

UIKIT_EXTERN NSString *const LFTextAttachmentToken; ///< Object replacement character (U+FFFC), used for text attachment.
UIKIT_EXTERN NSString *const LFTextTruncationToken; ///< Horizontal ellipsis (U+2026), used for text truncation  "…".



#pragma mark - Attribute Value Define

/**
 The tap/long press action callback defined in LFText.
 
 @param containerView The text container view (such as LFLabel/LFTextView).
 @param text          The whole text.
 @param range         The text range in `text`.
 @param rect          The text frame in `containerView`.
 */
typedef void(^LFTextAction)(UIView *containerView, NSAttributedString *text, NSRange range, CGRect rect);


/**
 LFTextBackedString objects are used by the NSAttributedString class cluster
 as the values for text backed string attributes (stored in the attributed 
 string under the key named LFTextBackedStringAttributeName).
 
 It may used for copy/paste plain text from attributed string.
 Example: If :) is replace by a custom emoji (such as😊), the backed string can be set to @":)".
 */
@interface LFTextBackedString : NSObject <NSCoding,NSCopying>
+ (instancetype)stringWithString:(NSString *)string;
@property (nonatomic, copy) NSString *string; ///< backed string
@end


/**
 LFTextBinding objects are used by the NSAttributedString class cluster
 as the values for shadow attributes (stored in the attributed string under
 the key named LFTextBindingAttributeName).
 
 Add this to a range of text will make the specified characters 'binding together'.
 LFTextView will treat the range of text as a single character during text 
 selection and edit.
 */
@interface LFTextBinding : NSObject <NSCoding, NSCopying>
+ (instancetype)bindingWithDeleteConfirm:(BOOL)deleteConfirm;
@property (nonatomic, assign) BOOL deleteConfirm; ///< confirm the range when delete in LFTextView
@end


/**
 LFTextShadow objects are used by the NSAttributedString class cluster
 as the values for shadow attributes (stored in the attributed string under
 the key named LFTextShadowAttributeName or LFTextInnerShadowAttributeName).
 
 It's similar to `NSShadow`, but offers more options.
 */
@interface LFTextShadow : NSObject <NSCoding, NSCopying>
+ (instancetype)shadowWithColor:(UIColor *)color offset:(CGSize)offset radius:(CGFloat)radius;

@property (nonatomic, strong) UIColor *color;           ///< shadow color
@property (nonatomic, assign) CGSize offset;            ///< shadow offset
@property (nonatomic, assign) CGFloat radius;           ///< shadow blur radius
@property (nonatomic, assign) CGBlendMode blendMode;    ///< shadow blend mode
@property (nonatomic, strong) LFTextShadow *subShadow;  ///< a sub shadow which will be added above the parent shadow

+ (instancetype)shadowWithNSShadow:(NSShadow *)nsShadow; ///< convert NSShadow to LFTextShadow
- (NSShadow *)nsShadow; ///< convert LFTextShadow to NSShadow
@end


/**
 LFTextDecorationLine objects are used by the NSAttributedString class cluster
 as the values for decoration line attributes (stored in the attributed string under
 the key named LFTextUnderlineAttributeName or LFTextStrikethroughAttributeName).
 
 When it's used as underline, the line is drawn below text glyphs;
 when it's used as strikethrough, the line is drawn above text glyphs.
 */
@interface LFTextDecoration : NSObject <NSCoding, NSCopying>
+ (instancetype)decorationWithStyle:(LFTextLineStyle)style;
+ (instancetype)decorationWithStyle:(LFTextLineStyle)style width:(NSNumber *)width color:(UIColor *)color;
@property (nonatomic, assign) LFTextLineStyle style; ///< line style
@property (nonatomic, strong) NSNumber *width;       ///< line width (nil means automatic width)
@property (nonatomic, strong) UIColor *color;        ///< line color (nil means automatic color)
@property (nonatomic, strong) LFTextShadow *shadow;  ///< line shadow
@end


/**
 LFTextBorder objects are used by the NSAttributedString class cluster
 as the values for border attributes (stored in the attributed string under
 the key named LFTextBorderAttributeName or LFTextBackgroundBorderAttributeName).
 
 It can be used to draw a border around a range of text, or draw a background
 to a range of text.
 
 Example:
    ╭─────╮
    │ Text │
    ╰─────╯
 */
@interface LFTextBorder : NSObject <NSCoding, NSCopying>
+ (instancetype)borderWithLineStyle:(LFTextLineStyle)lineStyle lineWidth:(CGFloat)width strokeColor:(UIColor *)color;
+ (instancetype)borderWithFillColor:(UIColor *)color cornerRadius:(CGFloat)cornerRadius;
@property (nonatomic, assign) LFTextLineStyle lineStyle; ///< border line style
@property (nonatomic, assign) CGFloat strokeWidth;       ///< border line width
@property (nonatomic, strong) UIColor *strokeColor;      ///< border line color
@property (nonatomic, assign) CGLineJoin lineJoin;       ///< border line join
@property (nonatomic, assign) UIEdgeInsets insets;       ///< border insets for text bounds
@property (nonatomic, assign) CGFloat cornerRadius;      ///< border corder radius
@property (nonatomic, strong) LFTextShadow *shadow;      ///< border shadow
@property (nonatomic, strong) UIColor *fillColor;        ///< inner fill color
@end


/**
 LFTextAttachment objects are used by the NSAttributedString class cluster 
 as the values for attachment attributes (stored in the attributed string under 
 the key named LFTextAttachmentAttributeName).
 
 When display an attributed string which contains `LFTextAttachment` object,
 the content will be placed in text metric. If the content is `UIImage`, 
 then it will be drawn to CGContext; if the content is `UIView` or `CALayer`, 
 then it will be added to the text container's view or layer.
 */
@interface LFTextAttachment : NSObject<NSCoding, NSCopying>
+ (instancetype)attachmentWithContent:(id)content;
@property (nonatomic, strong) id content;                    ///< Supported type: UIImage, UIView, CALayer
@property (nonatomic, assign) UIViewContentMode contentMode; ///< Content display mode.
@property (nonatomic, assign) UIEdgeInsets contentInsets;    ///< The insets when drawing content.
@property (nonatomic, strong) NSDictionary *userInfo;        ///< The user information dictionary.
@end


/**
 高亮。有该属性的文本范围可以被用户点击。
 当点下去时，highlight.attributes 中的属性会替换掉原始的属性。
 
 LFTextHighlight objects are used by the NSAttributedString class cluster
 as the values for touchable highlight attributes (stored in the attributed string
 under the key named LFTextHighlightAttributeName).
 
 When display an attributed string in `LFLabel` or `LFTextView`, the range of 
 highlight text can be toucheds down by users. If a range of text is turned into 
 highlighted state, the `attributes` in `LFTextHighlight` will be used to modify 
 (set or remove) the original attributes in the range for display.
 */
@interface LFTextHighlight : NSObject <NSCoding, NSCopying>
/**
 Attributes that you can apply to text in an attributed string when highlight.
 Key:   Same as CoreText/LFText Attribute Name.
 Value: Modify attribute value when highlight (NSNull for remove attribute).
 */
@property (nonatomic, copy) NSDictionary *attributes;

+ (instancetype)highlightWithAttributes:(NSDictionary *)attributes;

// Convenience methods below to set the `attributes`.
- (void)setFont:(UIFont *)font;
- (void)setColor:(UIColor *)color;
- (void)setStrokeWidth:(NSNumber *)width;
- (void)setStrokeColor:(UIColor *)color;
- (void)setShadow:(LFTextShadow *)shadow;
- (void)setInnerShadow:(LFTextShadow *)shadow;
- (void)setUnderline:(LFTextDecoration *)underline;
- (void)setStrikethrough:(LFTextDecoration *)strikethrough;
- (void)setBackgroundBorder:(LFTextBorder *)border;
- (void)setBorder:(LFTextBorder *)border;
- (void)setAttachment:(LFTextAttachment *)attachment;

/**
 The user information dictionary.
 */
@property (nonatomic, copy) NSDictionary *userInfo;

/**
 Tap action when user tap the highlight.
 If the value is nil, LFTextView or LFLabel will ask it's delegate to deal with tap action.
 */
@property (nonatomic, copy) LFTextAction tapAction;

/**
 Long press action when user long press the highlight.
 If the value is nil, LFTextView or LFLabel will ask it's delegate to deal with long press action.
 */
@property (nonatomic, copy) LFTextAction longPressAction;

@end


#endif
