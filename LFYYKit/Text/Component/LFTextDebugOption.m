//
//  LFTextDebugOption.m

//  Created by guoyaoyuan on 15/4/8.
//  
//
//  This source code is licensed under the MIT-style license found in the
//  LICENSE file in the root directory of this source tree.
//

#import "LFTextDebugOption.h"
#import <LFCategory/LFCategory.h>
#import <libkern/OSAtomic.h>
#import <pthread.h>


/**
 Initialize a pthread mutex.
 */
static inline void pthread_mutex_init_recursive(pthread_mutex_t *mutex, bool recursive) {
#define MUTEX_ASSERT_ON_ERROR(x_) do { \
__unused volatile int res = (x_); \
assert(res == 0); \
} while (0)
    assert(mutex != NULL);
    if (!recursive) {
        MUTEX_ASSERT_ON_ERROR(pthread_mutex_init(mutex, NULL));
    } else {
        pthread_mutexattr_t attr;
        MUTEX_ASSERT_ON_ERROR(pthread_mutexattr_init (&attr));
        MUTEX_ASSERT_ON_ERROR(pthread_mutexattr_settype (&attr, PTHREAD_MUTEX_RECURSIVE));
        MUTEX_ASSERT_ON_ERROR(pthread_mutex_init (mutex, &attr));
        MUTEX_ASSERT_ON_ERROR(pthread_mutexattr_destroy (&attr));
    }
#undef MUTEX_ASSERT_ON_ERROR
}


static pthread_mutex_t _sharedDebugLock;
static CFMutableSetRef _sharedDebugTargets = nil;
static LFTextDebugOption *_sharedDebugOption = nil;

static const void* _sharedDebugSetRetain(CFAllocatorRef allocator, const void *value) {
    return value;
}

static void _sharedDebugSetRelease(CFAllocatorRef allocator, const void *value) {
}

void _sharedDebugSetFunction(const void *value, void *context) {
    id<LFTextDebugTarget> target = (__bridge id<LFTextDebugTarget>)(value);
    [target setDebugOption:_sharedDebugOption];
}

static void _initSharedDebug() {
    static dispatch_once_t onceToken;
    dispatch_once(&onceToken, ^{
        pthread_mutex_init_recursive(&_sharedDebugLock, false);
        CFSetCallBacks callbacks = kCFTypeSetCallBacks;
        callbacks.retain = _sharedDebugSetRetain;
        callbacks.release = _sharedDebugSetRelease;
        _sharedDebugTargets = CFSetCreateMutable(CFAllocatorGetDefault(), 0, &callbacks);
    });
}

static void _setSharedDebugOption(LFTextDebugOption *option) {
    _initSharedDebug();
    pthread_mutex_lock(&_sharedDebugLock);
    _sharedDebugOption = option.copy;
    CFSetApplyFunction(_sharedDebugTargets, _sharedDebugSetFunction, NULL);
    pthread_mutex_unlock(&_sharedDebugLock);
}

static LFTextDebugOption *_getSharedDebugOption() {
    _initSharedDebug();
    pthread_mutex_lock(&_sharedDebugLock);
    LFTextDebugOption *op = _sharedDebugOption;
    pthread_mutex_unlock(&_sharedDebugLock);
    return op;
}

static void _addDebugTarget(id<LFTextDebugTarget> target) {
    _initSharedDebug();
    pthread_mutex_lock(&_sharedDebugLock);
    CFSetAddValue(_sharedDebugTargets, (__bridge const void *)(target));
    pthread_mutex_unlock(&_sharedDebugLock);
}

static void _removeDebugTarget(id<LFTextDebugTarget> target) {
    _initSharedDebug();
    pthread_mutex_lock(&_sharedDebugLock);
    CFSetRemoveValue(_sharedDebugTargets, (__bridge const void *)(target));
    pthread_mutex_unlock(&_sharedDebugLock);
}


@implementation LFTextDebugOption

- (id)copyWithZone:(NSZone *)zone {
    LFTextDebugOption *op = [self.class new];
    op.baselineColor = self.baselineColor;
    op.CTFrameBorderColor = self.CTFrameBorderColor;
    op.CTFrameFillColor = self.CTFrameFillColor;
    op.CTLineBorderColor = self.CTLineBorderColor;
    op.CTLineFillColor = self.CTLineFillColor;
    op.CTLineNumberColor = self.CTLineNumberColor;
    op.CTRunBorderColor = self.CTRunBorderColor;
    op.CTRunFillColor = self.CTRunFillColor;
    op.CTRunNumberColor = self.CTRunNumberColor;
    op.CGGlyphBorderColor = self.CGGlyphBorderColor;
    op.CGGlyphFillColor = self.CGGlyphFillColor;
    return op;
}

- (BOOL)needDrawDebug {
    if (self.baselineColor.alpha > 0 ||
        self.CTFrameBorderColor.alpha > 0 ||
        self.CTFrameFillColor.alpha > 0 ||
        self.CTLineBorderColor.alpha > 0 ||
        self.CTLineFillColor.alpha > 0 ||
        self.CTLineNumberColor.alpha > 0 ||
        self.CTRunBorderColor.alpha > 0 ||
        self.CTRunFillColor.alpha > 0 ||
        self.CTRunNumberColor.alpha > 0 ||
        self.CGGlyphBorderColor.alpha > 0 ||
        self.CGGlyphFillColor.alpha > 0) return YES;
    return NO;
}

- (void)clear {
    self.baselineColor = nil;
    self.CTFrameBorderColor = nil;
    self.CTFrameFillColor = nil;
    self.CTLineBorderColor = nil;
    self.CTLineFillColor = nil;
    self.CTLineNumberColor = nil;
    self.CTRunBorderColor = nil;
    self.CTRunFillColor = nil;
    self.CTRunNumberColor = nil;
    self.CGGlyphBorderColor = nil;
    self.CGGlyphFillColor = nil;
}

+ (void)addDebugTarget:(id<LFTextDebugTarget>)target {
    if (target) _addDebugTarget(target);
}

+ (void)removeDebugTarget:(id<LFTextDebugTarget>)target {
    if (target) _removeDebugTarget(target);
}

+ (LFTextDebugOption *)sharedDebugOption {
    return _getSharedDebugOption();
}

+ (void)setSharedDebugOption:(LFTextDebugOption *)option {
    _setSharedDebugOption(option);
}

@end

