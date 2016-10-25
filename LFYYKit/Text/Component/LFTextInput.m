//
//  LFTextInput.m

//  Created by guoyaoyuan on 15/4/17.
//  
//
//  This source code is licensed under the MIT-style license found in the
//  LICENSE file in the root directory of this source tree.
//

#import "LFTextInput.h"
#import <LFCategory/LFCategory.h>

@implementation LFTextPosition

+ (instancetype)positionWithOffset:(NSInteger)offset {
    return [self positionWithOffset:offset affinity:LFTextAffinityForward];
}

+ (instancetype)positionWithOffset:(NSInteger)offset affinity:(LFTextAffinity)affinity {
    LFTextPosition *p = [self new];
    p->_offset = offset;
    p->_affinity = affinity;
    return p;
}

- (instancetype)copyWithZone:(NSZone *)zone {
    return [self.class positionWithOffset:_offset affinity:_affinity];
}

- (NSString *)description {
    return [NSString stringWithFormat:@"<%@: %p> (%@%@)", self.class, self, @(_offset), _affinity == LFTextAffinityForward ? @"F":@"B"];
}

- (NSUInteger)hash {
    return _offset * 2 + (_affinity == LFTextAffinityForward ? 1 : 0);
}

- (BOOL)isEqual:(LFTextPosition *)object {
    if (!object) return NO;
    return _offset == object.offset && _affinity == object.affinity;
}

- (NSComparisonResult)compare:(LFTextPosition *)otherPosition {
    if (!otherPosition) return NSOrderedAscending;
    if (_offset < otherPosition.offset) return NSOrderedAscending;
    if (_offset > otherPosition.offset) return NSOrderedDescending;
    if (_affinity == LFTextAffinityBackward && otherPosition.affinity == LFTextAffinityForward) return NSOrderedAscending;
    if (_affinity == LFTextAffinityForward && otherPosition.affinity == LFTextAffinityBackward) return NSOrderedDescending;
    return NSOrderedSame;
}

@end



@implementation LFTextRange {
    LFTextPosition *_start;
    LFTextPosition *_end;
}

- (instancetype)init {
    self = [super init];
    if (!self) return nil;
    _start = [LFTextPosition positionWithOffset:0];
    _end = [LFTextPosition positionWithOffset:0];
    return self;
}

- (LFTextPosition *)start {
    return _start;
}

- (LFTextPosition *)end {
    return _end;
}

- (BOOL)isEmpty {
    return _start.offset == _end.offset;
}

- (NSRange)asRange {
    return NSMakeRange(_start.offset, _end.offset - _start.offset);
}

+ (instancetype)rangeWithRange:(NSRange)range {
    return [self rangeWithRange:range affinity:LFTextAffinityForward];
}

+ (instancetype)rangeWithRange:(NSRange)range affinity:(LFTextAffinity)affinity {
    LFTextPosition *start = [LFTextPosition positionWithOffset:range.location affinity:affinity];
    LFTextPosition *end = [LFTextPosition positionWithOffset:range.location + range.length affinity:affinity];
    return [self rangeWithStart:start end:end];
}

+ (instancetype)rangeWithStart:(LFTextPosition *)start end:(LFTextPosition *)end {
    if (!start || !end) return nil;
    if ([start compare:end] == NSOrderedDescending) {
        LF_SWAP(start, end);
    }
    LFTextRange *range = [LFTextRange new];
    range->_start = start;
    range->_end = end;
    return range;
}

+ (instancetype)defaultRange {
    return [self new];
}

- (instancetype)copyWithZone:(NSZone *)zone {
    return [self.class rangeWithStart:_start end:_end];
}

- (NSString *)description {
    return [NSString stringWithFormat:@"<%@: %p> (%@, %@)%@", self.class, self, @(_start.offset), @(_end.offset - _start.offset), _end.affinity == LFTextAffinityForward ? @"F":@"B"];
}

- (NSUInteger)hash {
    return (sizeof(NSUInteger) == 8 ? OSSwapInt64(_start.hash) : OSSwapInt32(_start.hash)) + _end.hash;
}

- (BOOL)isEqual:(LFTextRange *)object {
    if (!object) return NO;
    return [_start isEqual:object.start] && [_end isEqual:object.end];
}

@end



@implementation LFTextSelectionRect

@synthesize rect = _rect;
@synthesize writingDirection = _writingDirection;
@synthesize containsStart = _containsStart;
@synthesize containsEnd = _containsEnd;
@synthesize isVertical = _isVertical;

- (id)copyWithZone:(NSZone *)zone {
    LFTextSelectionRect *one = [self.class new];
    one.rect = _rect;
    one.writingDirection = _writingDirection;
    one.containsStart = _containsStart;
    one.containsEnd = _containsEnd;
    one.isVertical = _isVertical;
    return one;
}

@end
