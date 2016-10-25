//
//  LFTextView.h
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

@class LFTextView;

/**
 The LFTextViewDelegate protocol defines a set of optional methods you can use
 to receive editing-related messages for LFTextView objects. 
 
 @discussion The API and behavior is similar to UITextViewDelegate,
 see UITextViewDelegate's documentation for more information.
 */
@protocol LFTextViewDelegate <NSObject, UIScrollViewDelegate>
@optional
- (BOOL)textViewShouldBeginEditing:(LFTextView *)textView;
- (BOOL)textViewShouldEndEditing:(LFTextView *)textView;
- (void)textViewDidBeginEditing:(LFTextView *)textView;
- (void)textViewDidEndEditing:(LFTextView *)textView;
- (BOOL)textView:(LFTextView *)textView shouldChangeTextInRange:(NSRange)range replacementText:(NSString *)text;
- (void)textViewDidChange:(LFTextView *)textView;
- (void)textViewDidChangeSelection:(LFTextView *)textView;

- (BOOL)textView:(LFTextView *)textView shouldTapHighlight:(LFTextHighlight *)highlight inRange:(NSRange)characterRange;
- (void)textView:(LFTextView *)textView didTapHighlight:(LFTextHighlight *)highlight inRange:(NSRange)characterRange rect:(CGRect)rect;
- (BOOL)textView:(LFTextView *)textView shouldLongPressHighlight:(LFTextHighlight *)highlight inRange:(NSRange)characterRange;
- (void)textView:(LFTextView *)textView didLongPressHighlight:(LFTextHighlight *)highlight inRange:(NSRange)characterRange rect:(CGRect)rect;
@end



/**
 LFTextView 是一个 UITextView 的开源实现，有着和 UITextView 相似的 API，并提供了以下更多的功能：
 
 * 扩展了 CoreText 的属性以支持更多文字效果。
 * 支持嵌入 UIImage/UIView/CALayer 作为图文混排元素。
 * 支持添加 "highlight" 高亮文本区域，用于链接点击和长按。
 * 支持直接控制文本绘制的区域，用于处理文字环绕等需求。
 * 支持竖排版，用于显示中日韩文字。
 * 支持图片和富文本的复制粘贴。
 * 支持富文本 placeholder。
 
 See NSAttributedString+LFText.h for more convenience methods to set the attributes.
 See LFTextAttribute.h and LFTextLayout.h for more information.
 */
@interface LFTextView : UIScrollView <UITextInput>


#pragma mark - Accessing the Delegate
///=============================================================================
/// @name Accessing the Delegate
///=============================================================================

@property (nonatomic, weak) id<LFTextViewDelegate> delegate;


#pragma mark - Configuring the Text Attributes
///=============================================================================
/// @name Configuring the Text Attributes
///=============================================================================

/**
 The text displayed by the text view.
 Set a new value to this property also replaces the text in `attributedText`.
 Get the value returns the plain text in `attributedText`.
 */
@property (nonatomic, copy) NSString *text;

/**
 The font of the text. Default is 12-point system font.
 Set a new value to this property also causes the new font to be applied to the entire `attributedText`.
 Get the value returns the font at the head of `attributedText`.
 */
@property (nonatomic, strong) UIFont *font;

/**
 The color of the text. Default is black.
 Set a new value to this property also causes the new color to be applied to the entire `attributedText`.
 Get the value returns the color at the head of `attributedText`.
 */
@property (nonatomic, strong) UIColor *textColor;

/**
 The technique to use for aligning the text. Default is NSLeftTextAlignment.
 Set a new value to this property also causes the new alignment to be applied to the entire `attributedText`.
 Get the value returns the alignment at the head of `attributedText`.
 */
@property (nonatomic, assign) NSTextAlignment textAlignment;

/**
 The text vertical aligmnent in container. Default is LFTextVerticalAlignmentTop.
 */
@property (nonatomic, assign) LFTextVerticalAlignment textVerticalAlignment;

/**
 The types of data converted to clickable URLs in the text view. Default is UIDataDetectorTypeNone.
 The tap or long press action should be handled by delegate.
 */
@property (nonatomic, assign) UIDataDetectorTypes dataDetectorTypes;

/**
 The attributes to apply to links at normal state. Default is light blue color.
 When a range of text is detected by the `dataDetectorTypes`, this value would be
 used to modify the original attributes in the range.
 */
@property (nonatomic, copy) NSDictionary *linkTextAttributes;

/**
 The attributes to apply to links at highlight state. Default is a gray border.
 When a range of text is detected by the `dataDetectorTypes` and the range was touched by user,
 this value would be used to modify the original attributes in the range.
 */
@property (nonatomic, copy) NSDictionary *highlightTextAttributes;

/**
 The attributes to apply to new text being entered by the user.
 When the text view's selection changes, this value is reset automatically.
 */
@property (nonatomic, copy) NSDictionary *typingAttributes;

/**
 The styled text displayed by the text view.
 Set a new value to this property also replaces the value of the `text`, `font`, `textColor`,
 `textAlignment` and other properties in text view.
 
 @discussion It only support the attributes declared in CoreText and LFTextAttribute.
 See `NSAttributedString+LFText` for more convenience methods to set the attributes.
 */
@property (nonatomic, copy) NSAttributedString *attributedText;

/**
 When `text` or `attributedText` is changed, the parser will be called to modify the text.
 It can be used to add code highlighting or emoticon replacement to text view.
 The default value is nil.
 
 See `LFTextParser` protocol for more information.
 */
@property (nonatomic, strong) id<LFTextParser> textParser;

/**
 The current text layout in text view (readonly).
 It can be used to query the text layout information.
 */
@property (nonatomic, strong, readonly) LFTextLayout *textLayout;


#pragma mark - Configuring the Placeholder
///=============================================================================
/// @name Configuring the Placeholder
///=============================================================================

/**
 The placeholder text displayed by the text view (when the text view is empty).
 Set a new value to this property also replaces the text in `placeholderAttributedText`.
 Get the value returns the plain text in `placeholderAttributedText`.
 */
@property (nonatomic, copy) NSString *placeholderText;

/**
 The font of the placeholder text. Default is same as `font` property.
 Set a new value to this property also causes the new font to be applied to the entire `placeholderAttributedText`.
 Get the value returns the font at the head of `placeholderAttributedText`.
 */
@property (nonatomic, strong) UIFont *placeholderFont;

/**
 The color of the placeholder text. Default is gray.
 Set a new value to this property also causes the new color to be applied to the entire `placeholderAttributedText`.
 Get the value returns the color at the head of `placeholderAttributedText`.
 */
@property (nonatomic, strong) UIColor *placeholderTextColor;

/**
 The styled placeholder text displayed by the text view (when the text view is empty).
 Set a new value to this property also replaces the value of the `placeholderText`, 
 `placeholderFont`, `placeholderTextColor`.
 
 @discussion It only support the attributes declared in CoreText and LFTextAttribute.
 See `NSAttributedString+LFText` for more convenience methods to set the attributes.
 */
@property (nonatomic, copy) NSAttributedString *placeholderAttributedText;


#pragma mark - Configuring the Text Container
///=============================================================================
/// @name Configuring the Text Container
///=============================================================================

/**
 The inset of the text container's layout area within the text view's content area.
 */
@property (nonatomic, assign) UIEdgeInsets textContainerInset;

/**
 An array of UIBezierPath objects representing the exclusion paths inside the 
 receiver's bounding rectangle. Default value is nil.
 */
@property (nonatomic, copy) NSArray *exclusionPaths;

/**
 Whether the receiver's layout orientation is vertical form. Default is NO.
 It may used to edit/display CJK text.
 */
@property (nonatomic, assign, getter=isVerticalForm) BOOL verticalForm;

/**
 The text line position modifier used to modify the lines' position in layout.
 See `LFTextLinePositionModifier` protocol for more information.
 */
@property (nonatomic, copy) id<LFTextLinePositionModifier> linePositionModifier;

/**
 The debug option to display CoreText layout result.
 The default value is [LFTextDebugOption sharedDebugOption].
 */
@property (nonatomic, copy) LFTextDebugOption *debugOption;


#pragma mark - Working with the Selection and Menu
///=============================================================================
/// @name Working with the Selection and Menu
///=============================================================================

/**
 Scrolls the receiver until the text in the specified range is visible.
 */
- (void)scrollRangeToVisible:(NSRange)range;

/**
 The current selection range of the receiver.
 */
@property (nonatomic, assign) NSRange selectedRange;

/**
 A Boolean value indicating whether inserting text replaces the previous contents.
 The default value is NO.
 */
@property (nonatomic, assign) BOOL clearsOnInsertion;

/**
 A Boolean value indicating whether the receiver is selectable. Default is YES.
 When the value of this property is NO, user cannot select content or edit text.
 */
@property (nonatomic, getter=isSelectable) BOOL selectable;

/**
 A Boolean value indicating whether the receiver is highlightable. Default is YES.
 When the value of this property is NO, user cannot interact with the highlight range of text.
 */
@property (nonatomic, getter=isHighlightable) BOOL highlightable;

/**
 A Boolean value indicating whether the receiver is editable. Default is YES.
 When the value of this property is NO, user cannot edit text.
 */
@property (nonatomic, getter=isEditable) BOOL editable;

/**
 A Boolean value indicating whether the receiver can paste image from pasteboard. Default is NO.
 When the value of this property is YES, user can paste image from pasteboard via menu.
 */
@property (nonatomic, assign) BOOL allowsPasteImage;

/**
 A Boolean value indicating whether the receiver can paste attributed text from pasteboard. Default is NO.
 When the value of this property is YES, user can paste attributed text from pasteboard via menu.
 */
@property (nonatomic, assign) BOOL allowsPasteAttributedString;


#pragma mark - Manage the undo and redo
///=============================================================================
/// @name Manage the undo and redo
///=============================================================================

/**
 A Boolean value indicating whether the receiver can undo and redo typing with
 shake gesture. The default value is YES.
 */
@property (nonatomic, assign) BOOL allowsUndoAndRedo;

/**
 The maximum undo/redo level. The default value is 20.
 */
@property (nonatomic, assign) NSUInteger maximumUndoLevel;


#pragma mark - Replacing the System Input Views
///=============================================================================
/// @name Replacing the System Input Views
///=============================================================================

/**
 设置该值后，该视图将会替换掉系统键盘。设置完成后需要调用 'reloadInputViews' 来通知系统。
 
 The custom input view to display when the text view becomes the first responder.
 It can be used to replace system keyboard.
 
 @discussion If set the value while first responder, it will not take effect until 
 'reloadInputViews' is called.
 */
@property (readwrite, retain) UIView *inputView;

/**
 设置该值后，该视图将会放在键盘的上方作为工具条。设置完成后需要调用 'reloadInputViews' 来通知系统。
 
 The custom accessory view to display when the text view becomes the first responder.
 It can be used to add a toolbar at the top of keyboard.
 
 @discussion If set the value while first responder, it will not take effect until
 'reloadInputViews' is called.
 */
@property (readwrite, retain) UIView *inputAccessoryView;

/**
 如果你用的是自己的键盘工具条，可以把工具条高度设置在这里。TextView 处理自动滚动等事件时会用到。
 
 If you use an custom accessory view without "inputAccessoryView" property,
 you may set the accessory view's height. It may used by auto scroll calculation.
 */
@property (nonatomic, assign) CGFloat extraAccessoryViewHeight;

@end


// Notifications, see UITextView's documentation for more information.
UIKIT_EXTERN NSString *const LFTextViewTextDidBeginEditingNotification;
UIKIT_EXTERN NSString *const LFTextViewTextDidChangeNotification;
UIKIT_EXTERN NSString *const LFTextViewTextDidEndEditingNotification;
