//
//  LFFrameImage.m
//  LaiFeng
//
//  Created by guoyaoyuan on 14-10-28.
//  Copyright (c) 2014年 live Interactive. All rights reserved.
//

#import "LFFrameImage.h"
#import <LFCategory/LFCategory.h>

@implementation LFFrameImage {
    NSArray *_paths;
    NSArray *_durations;
}

- (LFFrameImage *)initWithFilePaths:(NSArray *)paths frameDuration:(NSTimeInterval)oneFrameDuration{
    
    NSMutableArray *arr = @[].mutableCopy;
    for (int i = 0; i < paths.count; i++) {
        [arr addObject:@(oneFrameDuration)];
    }
    return [self initWithFilePaths:paths frameDurations:arr];
}

- (LFFrameImage *)initWithFilePaths:(NSArray *)paths frameDurations:(NSArray *)durations {
    if (paths.count <1 || durations.count < 1 || paths.count != durations.count) return nil;
    
    UIImage *img = [[UIImage alloc] initWithContentsOfFile:paths[0]];
    img = [img lf_imageByDecoded];
    self = [self initWithCGImage:img.CGImage scale:1 orientation:UIImageOrientationUp];
    if (!self) return nil;
    _paths = paths.copy;
    _durations = durations.copy;
    self.repeat = YES;
    return self;
}

- (NSUInteger)animatedImageCount {
    return _paths.count;
}

- (NSUInteger)animatedImageRepeatCount {
    return self.repeat ? 0 : 1;
}

- (NSUInteger)animatedImageBytesPerFrame {
    return self.size.width * self.size.height * self.scale * 4;
}

- (UIImage *)animatedImageAtIndex:(NSUInteger)index {
    NSUInteger i = index % _paths.count;
    if (i == 0) return self;
    UIImage *img = [[UIImage alloc] initWithContentsOfFile:_paths[i]];
    img = [img lf_imageByDecoded];
    return [[UIImage alloc] initWithCGImage:img.CGImage scale:1 orientation:UIImageOrientationUp];
}

- (NSTimeInterval)animatedImageDurationAtIndex:(NSUInteger)index {
    return ((NSNumber *)_durations[index]).doubleValue;
}

@end
