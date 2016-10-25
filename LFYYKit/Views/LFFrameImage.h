//
//  LFFrameImage.h
//  LaiFeng
//
//  Created by guoyaoyuan on 14-10-28.
//  Copyright (c) 2014年 live Interactive. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "LFAnimatedImageView.h"

/**
 可以显示帧动画的 Image。
 
 @discussion 该类和 UIImage 用法一样，可以作为 UIImage 的完整替代品。
 只有当被显示在 LFAnimatedImageView 里时，才会有动画效果。
 
 示例代码:
 NSArray *paths = @[@"/ani/1.png", @"/ani/2.png", @"/ani/3.png", @"/ani/4.png"];
 LFFrameImage *image = [[LFFrameImage alloc] initWithFilePaths:paths frameDuration:1/60.0];
 LFAnimatedImageView *imageView = [LFAnimatedImageView alloc] initWithImage:image];
 [view addSubView:imageView];
 */
@interface LFFrameImage : UIImage <LFAnimatedImage>

@property (nonatomic, assign) BOOL repeat; /// 是否重复播放，default YES

- (LFFrameImage *)initWithFilePaths:(NSArray *)paths frameDuration:(NSTimeInterval)oneFrameDuration;

- (LFFrameImage *)initWithFilePaths:(NSArray *)paths frameDurations:(NSArray *)durations;

@end
