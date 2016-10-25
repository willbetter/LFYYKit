//
//  LFLabel.h
//  Created by guoyaoyuan on 15/2/25.
//  
//
//  This source code is licensed under the MIT-style license found in the
//  LICENSE file in the root directory of this source tree.
//

#import <UIKit/UIKit.h>
#import "LFTextParser.h"
#import "LFTextLayout.h"
#import "LFTextAttribute.h"


#if !TARGET_INTERFACE_BUILDER

/**
 LFLabel 是一个 UILabel 的开源实现，有着和 UILabel 相似的 API，并提供了以下更多的功能：
 
 * 支持异步排版和渲染。
 * 扩展了 CoreText 的属性以支持更多文字效果。
 * 支持嵌入 UIImage/UIView/CALayer 作为图文混排元素。
 * 支持添加 "highlight" 高亮文本区域，用于链接点击和长按。
 * 支持直接控制文本绘制的区域，用于处理文字环绕等需求。
 * 支持竖排版，用于显示中日韩文字。
 
 See NSAttributedString+LFText.h for more convenience methods to set the attributes.
 See LFTextAttribute.h and LFTextLayout.h for more information.
 
 ===============================================================================
 示例：
 
 
 表情/图文混排：
     // 此处也可以用 LFAnimatedImageView 和 LFGIFImage 来显示动态表情
     UIImage *image = [UIImage imageNamed:@"icon"];
     NSMutableAttributedString *attachText = [NSMutableAttributedString attachmentStringWithContent:image contentMode:UIViewContentModeCenter attachmentSize:imageView.size alignToFont:font alignment:LFTextVerticalAlignmentCenter];
     NSMutableAttributedString *text = [[NSMutableAttributedString alloc] initWithString:@"Hahahahaha:"];
     [text appendAttributedString:attachText];
     LFLabel *label = [LFLabel new];
     label.attributedText = text;
 
 
 文本阴影
     NSMutableAttributedString *text = [[NSMutableAttributedString alloc] initWithString:@"Hahahaha"];
     text.font = [UIFont boldSystemFontOfSize:30];
     text.color = [UIColor whiteColor];
     LFTextShadow *shadow = [LFTextShadow new];
     shadow.color = [UIColor colorWithWhite:0.000 alpha:0.490];
     shadow.offset = CGSizeMake(0, 1);
     shadow.radius = 5;
     [text setTextShadow:shadow range:NSMakeRange(2,3)];
     LFLabel *label = [LFLabel new];
     label.attributedText = text;
 
 
 点击链接
     NSMutableAttributedString *text = [[NSMutableAttributedString alloc] initWithString:@"Hahahahahah"];
     text.font = [UIFont boldSystemFontOfSize:30];
     text.color = [UIColor colorWithRed:0.093 green:0.492 blue:1.000 alpha:1.000];
     text.underlineColor = one.color;
     text.underlineStyle = NSUnderlineStyleSingle;
     
     // 按下时的文本变化
     LFTextBorder *border = [LFTextBorder new];
     border.cornerRadius = 3;
     border.insets = UIEdgeInsetsMake(0, -4, 0, -4);
     border.fillColor = [UIColor colorWithWhite:0.000 alpha:0.220];
     
     LFTextHighlight *highlight = [LFTextHighlight new];
     [highlight setBorder:border];
     highlight.tapAction = ^(UIView *containerView, NSAttributedString *text, NSRange range, CGRect rect) {
        // 点击回调也可以放到 LFLabel.highlightTapAction 来统一处理
        [_self showMessage:[NSString stringWithFormat:@"Tap: %@",[text.string substringWithRange:range]]];
     };
     [text setTextHighlight:highlight range:one.rangeOfAll];
     LFLabel *label = [LFLabel new];
     label.attributedText = text;
 
 
 计算文本高度
     NSMutableAttributedString *text = [[NSMutableAttributedString alloc] initWithString:@"Some Text"];
     
     LFTextContainer *container = [LFTextContainer new];
     container.size = CGSizeMake(100, CGFLOAT_MAX);
     container.maximumNumberOfRows = 0;
     LFTextLayout *layout = [LFTextLayout layoutWithContainer:container text:text];
     
     LFLabel *label = [LFLabel new];
     label.size = layout.textBoundingSize;
     label.textLayout = layout;
 
 */
@interface LFLabel : UIView <NSCoding>

#pragma mark - Accessing the Text Attributes
///=============================================================================
/// @name Accessing the Text Attributes
///=============================================================================

/**
 The text displayed by the label. Default is nil.
 Set a new value to this property also replaces the text in `attributedText`.
 Get the value returns the plain text in `attributedText`.
 */
@property (nullable, nonatomic, copy) NSString *text;

/**
 The font of the text. Default is 17-point system font.
 Set a new value to this property also causes the new font to be applied to the entire `attributedText`.
 Get the value returns the font at the head of `attributedText`.
 */
@property (null_resettable, nonatomic, strong) UIFont *font;

/**
 The color of the text. Default is black.
 Set a new value to this property also causes the new color to be applied to the entire `attributedText`.
 Get the value returns the color at the head of `attributedText`.
 */
@property (null_resettable, nonatomic, strong) UIColor *textColor;

/**
 The shadow color of the text. Default is nil.
 Set a new value to this property also causes the shadow color to be applied to the entire `attributedText`.
 Get the value returns the shadow color at the head of `attributedText`.
 */
@property (nullable, nonatomic, strong) UIColor *shadowColor;

/**
 The shadow offset of the text. Default is CGSizeZero.
 Set a new value to this property also causes the shadow offset to be applied to the entire `attributedText`.
 Get the value returns the shadow offset at the head of `attributedText`.
 */
@property (nonatomic) CGSize shadowOffset;

/**
 The shadow blur of the text. Default is 0.
 Set a new value to this property also causes the shadow blur to be applied to the entire `attributedText`.
 Get the value returns the shadow blur at the head of `attributedText`.
 */
@property (nonatomic) CGFloat shadowBlurRadius;

/**
 The technique to use for aligning the text. Default is NSLeftTextAlignment.
 Set a new value to this property also causes the new alignment to be applied to the entire `attributedText`.
 Get the value returns the alignment at the head of `attributedText`.
 */
@property (nonatomic) NSTextAlignment textAlignment;

/**
 The text vertical aligmnent in container. Default is LFTextVerticalAlignmentCenter.
 */
@property (nonatomic) LFTextVerticalAlignment textVerticalAlignment;

/**
 The styled text displayed by the label.
 Set a new value to this property also replaces the value of the `text`, `font`, `textColor`,
 `textAlignment` and other properties in label.
 
 @discussion It only support the attributes declared in CoreText and LFTextAttribute.
 See `NSAttributedString+LFText` for more convenience methods to set the attributes.
 */
@property (nullable, nonatomic, copy) NSAttributedString *attributedText;

/**
 The technique to use for wrapping and truncating the label's text.
 Default is NSLineBreakByTruncatingTail.
 */
@property (nonatomic) NSLineBreakMode lineBreakMode;

/**
 The truncation token string used when text is truncated. Default is nil.
 When the value is nil, the label use "…" as default truncation token.
 */
@property (nullable, nonatomic, copy) NSAttributedString *truncationToken;

/**
 The maximum number of lines to use for rendering text. Default value is 1.
 0 means no limit.
 */
@property (nonatomic) NSUInteger numberOfLines;

/**
 When `text` or `attributedText` is changed, the parser will be called to modify the text.
 It can be used to add code highlighting or emoticon replacement to text view. 
 The default value is nil.
 
 See `LFTextParser` protocol for more information.
 */
@property (nullable, nonatomic, strong) id<LFTextParser> textParser;

/**
 The current text layout in text view. It can be used to query the text layout information.
 Set a new value to this property also replaces most properties in this label, such as `text`,
 `color`, `attributedText`, `lineBreakMode`, `textContainerPath`, `exclusionPaths` and so on.
 */
@property (nullable, nonatomic, strong) LFTextLayout *textLayout;


#pragma mark - Configuring the Text Container
///=============================================================================
/// @name Configuring the Text Container
///=============================================================================

/**
 A UIBezierPath object that specifies the shape of the text frame. Default value is nil.
 */
@property (nullable, nonatomic, copy) UIBezierPath *textContainerPath;

/**
 An array of UIBezierPath objects representing the exclusion paths inside the
 receiver's bounding rectangle. Default value is nil.
 */
@property (nullable, nonatomic, copy) NSArray *exclusionPaths;

/**
 The inset of the text container's layout area within the text view's content area.
 Default value is UIEdgeInsetsZero.
 */
@property (nonatomic) UIEdgeInsets textContainerInset;

/**
 Whether the receiver's layout orientation is vertical form. Default is NO.
 It may used to display CJK text.
 */
@property (nonatomic, getter=isVerticalForm) BOOL verticalForm;

/**
 The text line position modifier used to modify the lines' position in layout.
 Default value is nil.
 See `LFTextLinePositionModifier` protocol for more information.
 */
@property (nullable, nonatomic, copy) id<LFTextLinePositionModifier> linePositionModifier;

/**
 The debug option to display CoreText layout result.
 The default value is [LFTextDebugOption sharedDebugOption].
 */
@property (nullable, nonatomic, copy) LFTextDebugOption *debugOption;


#pragma mark - Getting the Layout Constraints
///=============================================================================
/// @name Getting the Layout Constraints
///=============================================================================

/**
 The preferred maximum width (in points) for a multiline label.
 
 @discussion This property affects the size of the label when layout constraints 
     are applied to it. During layout, if the text extends beyond the width 
     specified by this property, the additional text is flowed to one or more new 
     lines, thereby increasing the height of the label. If the text is vertical 
     form, this value will match to text height.
 */
@property (nonatomic) CGFloat preferredMaxLayoutWidth;


#pragma mark - Interacting with Text Data
///=============================================================================
/// @name Interacting with Text Data
///=============================================================================

/**
 When user tap the label, this action will be called (similar to tap gesture).
 The default value is nil.
 */
@property (nullable, nonatomic, copy) LFTextAction textTapAction;

/**
 When user long press the label, this action will be called (similar to long press gesture).
 The default value is nil.
 */
@property (nullable, nonatomic, copy) LFTextAction textLongPressAction;

/**
 When user tap the highlight range of text, this action will be called.
 The default value is nil.
 */
@property (nullable, nonatomic, copy) LFTextAction highlightTapAction;

/**
 When user long press the highlight range of text, this action will be called.
 The default value is nil. 
 */
@property (nullable, nonatomic, copy) LFTextAction highlightLongPressAction;

#pragma mark - Configuring the Touch Mode

/**
 If value is YES, When user tap highlightTapAction, ignore textTapAction
 
 The default value is `NO`.
 */
@property (nonatomic) BOOL ignoreTextTapActionWhenHighlightTapAction;



#pragma mark - Configuring the Display Mode
///=============================================================================
/// @name Configuring the Display Mode
///=============================================================================

/**
 A Boolean value indicating whether the layout and rendering codes are running
 asynchronously on background threads. 
 
 The default value is `NO`.
 */
@property (nonatomic) BOOL displaysAsynchronously;

/**
 If the value is YES, and the layer is rendered asynchronously, then it will
 set label.layer.contents to nil before display. 
 
 The default value is `YES`.
 
 @discussion When the asynchronously display is enabled, the layer's content will
 be updated after the background render process finished. If the render process
 can not finished in a vsync time (1/60 second), the old content will be still kept
 for display. You may manually clear the content by set the layer.contents to nil 
 after you update the label's properties, or you can just set this property to YES.
 */
@property (nonatomic) BOOL clearContentsBeforeAsynchronouslyDisplay;

/**
 If the value is YES, and the layer is rendered asynchronously, then it will add 
 a fade animation on layer when the contents of layer changed. 
 
 The default value is `YES`.
 */
@property (nonatomic) BOOL fadeOnAsynchronouslyDisplay;

/**
 If the value is YES, then it will add a fade animation on layer when some range
 of text become highlighted. 
 
 The default value is `YES`.
 */
@property (nonatomic) BOOL fadeOnHighlight;

/**
 Ignore common properties (such as text, font, textColor, attributedText...) and
 only use "textLayout" to display content. 
 
 The default value is `NO`.
 
 @discussion If you control the label content only through "textLayout", then
 you may set this value to YES for higher performance.
 */
@property (nonatomic) BOOL ignoreCommonProperties;

/*
 Tips:
 
 1. If you only need a UILabel alternative to display rich text and receive link touch event, 
    you do not need to adjust the display mode properties.
 
 2. If you have performance issues, you may enable the asynchronous display mode
    by setting the `displaysAsynchronously` to YES.
 
 3. If you want to get the highest performance, you should do text layout with
    `LFTextLayout` class in background thread. Here's an example:
    
    YYLabel *label = [YYLabel new];
    label.displaysAsynchronously = YES;
    label.ignoreCommonProperties = YES;
    
    dispatch_async(dispatch_get_global_queue(DISPATCH_QUEUE_PRIORITY_DEFAULT, 0), ^{
 
        // Create attributed string.
        NSMutableAttributedString *text = [[NSMutableAttributedString alloc] initWithString:@"Some Text"];
        text.yy_font = [UIFont systemFontOfSize:16];
        text.yy_color = [UIColor grayColor];
        [text yy_setColor:[UIColor redColor] range:NSMakeRange(0, 4)];
 
        // Create text container
        LFTextContainer *container = [LFTextContainer new];
        container.size = CGSizeMake(100, CGFLOAT_MAX);
        container.maximumNumberOfRows = 0;
        
        // Generate a text layout.
        LFTextLayout *layout = [LFTextLayout layoutWithContainer:container text:text];
        
        dispatch_async(dispatch_get_main_queue(), ^{
            label.size = layout.textBoundingSize;
            label.textLayout = layout;
        });
    });
 
 */

@end


#else // TARGET_INTERFACE_BUILDER
IB_DESIGNABLE
@interface YYLabel : UIView <NSCoding>
@property (nullable, nonatomic, copy) IBInspectable NSString *text;
@property (null_resettable, nonatomic, strong) IBInspectable UIColor *textColor;
@property (nullable, nonatomic, strong) IBInspectable NSString *fontName_;
@property (nonatomic) IBInspectable CGFloat fontSize_;
@property (nonatomic) IBInspectable BOOL fontIsBold_;
@property (nonatomic) IBInspectable NSUInteger numberOfLines;
@property (nonatomic) IBInspectable NSInteger lineBreakMode;
@property (nonatomic) IBInspectable CGFloat preferredMaxLayoutWidth;
@property (nonatomic, getter=isVerticalForm) IBInspectable BOOL verticalForm;
@property (nonatomic) IBInspectable NSInteger textAlignment;
@property (nonatomic) IBInspectable NSInteger textVerticalAlignment;
@property (nullable, nonatomic, strong) IBInspectable UIColor *shadowColor;
@property (nonatomic) IBInspectable CGPoint shadowOffset;
@property (nonatomic) IBInspectable CGFloat shadowBlurRadius;
@property (nullable, nonatomic, copy) IBInspectable NSAttributedString *attributedText;
@property (nonatomic) IBInspectable CGFloat insetTop_;
@property (nonatomic) IBInspectable CGFloat insetBottom_;
@property (nonatomic) IBInspectable CGFloat insetLeft_;
@property (nonatomic) IBInspectable CGFloat insetRight_;
@property (nonatomic) IBInspectable BOOL debugEnabled_;

@property (null_resettable, nonatomic, strong) UIFont *font;
@property (nullable, nonatomic, copy) NSAttributedString *truncationToken;
@property (nullable, nonatomic, strong) id<LFTextParser> textParser;
@property (nullable, nonatomic, strong) LFTextLayout *textLayout;
@property (nullable, nonatomic, copy) UIBezierPath *textContainerPath;
@property (nullable, nonatomic, copy) NSArray *exclusionPaths;
@property (nonatomic) UIEdgeInsets textContainerInset;
@property (nullable, nonatomic, copy) id<LFTextLinePositionModifier> linePositionModifier;
@property (nonnull, nonatomic, copy) LFTextDebugOption *debugOption;
@property (nullable, nonatomic, copy) LFTextAction highlightTapAction;
@property (nullable, nonatomic, copy) LFTextAction highlightLongPressAction;
@property (nonatomic) BOOL displaysAsynchronously;
@property (nonatomic) BOOL clearContentsBeforeAsynchronouslyDisplay;
@property (nonatomic) BOOL fadeOnAsynchronouslyDisplay;
@property (nonatomic) BOOL fadeOnHighlight;
@property (nonatomic) BOOL ignoreCommonProperties;
@end
#endif // !TARGET_INTERFACE_BUILDER
