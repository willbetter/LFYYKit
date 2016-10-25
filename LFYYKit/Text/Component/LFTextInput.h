//
//  LFTextInput.h

//  Created by guoyaoyuan on 15/4/17.
//  
//
//  This source code is licensed under the MIT-style license found in the
//  LICENSE file in the root directory of this source tree.
//

#import <UIKit/UIKit.h>

/**
 Text position affinity. For example, the offset appears after the last
 character on a line is backward affinity, before the first character on
 the following line is forward affinity.
 */
typedef NS_ENUM(NSInteger, LFTextAffinity) {
    LFTextAffinityForward  = 0, ///< offset appears before the character
    LFTextAffinityBackward = 1, ///< offset appears after the character
};


/**
 A LFTextPosition object represents a position in a text container; in other words, 
 it is an index into the backing string in a text-displaying view.
 
 LFTextPosition has the same API as Apple's implementation in UITextView/UITextField,
 so you can alse use it to interact with UITextView/UITextField.
 */
@interface LFTextPosition : UITextPosition <NSCopying>

@property (nonatomic, readonly) NSInteger offset;
@property (nonatomic, readonly) LFTextAffinity affinity;

+ (instancetype)positionWithOffset:(NSInteger)offset;
+ (instancetype)positionWithOffset:(NSInteger)offset affinity:(LFTextAffinity) affinity;

- (NSComparisonResult)compare:(id)otherPosition;

@end


/**
 A LFTextRange object represents a range of characters in a text container; in other words, 
 it identifies a starting index and an ending index in string backing a text-displaying view.
 
 LFTextRange has the same API as Apple's implementation in UITextView/UITextField,
 so you can alse use it to interact with UITextView/UITextField.
 */
@interface LFTextRange : UITextRange <NSCopying>

@property (nonatomic, readonly) LFTextPosition *start;
@property (nonatomic, readonly) LFTextPosition *end;
@property (nonatomic, readonly, getter=isEmpty) BOOL empty;

+ (instancetype)rangeWithRange:(NSRange)range;
+ (instancetype)rangeWithRange:(NSRange)range affinity:(LFTextAffinity) affinity;
+ (instancetype)rangeWithStart:(LFTextPosition *)start end:(LFTextPosition *)end;
+ (instancetype)defaultRange; ///< <{0,0} Forward>

- (NSRange)asRange;

@end


/**
 A LFTextSelectionRect object encapsulates information about a selected range of 
 text in a text-displaying view.
 
 LFTextSelectionRect has the same API as Apple's implementation in UITextView/UITextField,
 so you can alse use it to interact with UITextView/UITextField.
 */
@interface LFTextSelectionRect : UITextSelectionRect <NSCopying>

@property (nonatomic, readwrite) CGRect rect;
@property (nonatomic, readwrite) UITextWritingDirection writingDirection;
@property (nonatomic, readwrite) BOOL containsStart;
@property (nonatomic, readwrite) BOOL containsEnd;
@property (nonatomic, readwrite) BOOL isVertical;

@end
