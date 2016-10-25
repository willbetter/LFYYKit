//
//  LFAnimatedImageView.h
//
//
//  Created by guoyaoyuan on 14/10/19.
//  Copyright (c) 2014 live Interactive. All rights reserved.
//

#import <UIKit/UIKit.h>

/**
 可以显示动画的 ImageView。
 
 @discussion 该类用法和 UIImageView 一样，并且可以作为 UIImageView 的完整替代品。
 只有当 .image 或 .highlightedImage 实现了 LFAnimatedImage 协议时，才会有动画。
 动画可以用 UIImageView的方法 -startAnimating`, `-stopAnimating` and `-isAnimating` 来控制。
 
 相对于其他方式显示动画，这个类能节省内存，并且提供较高精度的时间控制。
 
 @discussion 当该view被显示到屏幕时，动画才会开始播放。播放时会实时请求每一帧数据。
 如果设备当前空闲内存足够，内部会用缓存保存一部分帧(向前和向后)数据来节省CPU解码。
 缓存大小会根据当前设备的内存状况自动调整。
 
 示例代码:
     // icon@2x.gif
     LFGifImage *image = [LFGifImage imageNamed:@"icon"];
     LFAnimatedImageView *imageView = [LFAnimatedImageView alloc] initWithImage:image];
     [view addSubView:imageView];
 */
@interface LFAnimatedImageView : UIImageView
@property (nonatomic, readonly) NSUInteger curIndex; ///< 当前播放到第几帧
@property (nonatomic, copy) void (^frameChanged)(NSUInteger curIndex); ///< 每帧播放回调。。hack。。没时间搞了
@property (nonatomic, copy) void (^loopEndAction)(); ///< 当loop结束后调用
@end





/**
 LFAnimatedImage 协议。实现该协议的 UIImage 都可以放到 LFAnimatedImageView 来显示动画。
 */
@protocol LFAnimatedImage <NSObject>
@required

/// 总图片数.
- (NSUInteger)animatedImageCount;

/// 动画重复次数. 0表示无限循环.
- (NSUInteger)animatedImageRepeatCount;

/// 每帧的 Bytes (用来优化内存缓存)
- (NSUInteger)animatedImageBytesPerFrame;

/// 返回一帧图片 (该方法将在后台线程被调用).
/// @param index  Index from 0.
- (UIImage *)animatedImageAtIndex:(NSUInteger)index;

/// 返回一帧图片的显示时间
/// @param index  Index from 0.
- (NSTimeInterval)animatedImageDurationAtIndex:(NSUInteger)index;

@end
