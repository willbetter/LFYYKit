//
//  LFGIFImage.h
//
//
//  Created by guoyaoyuan on 14/10/20.
//  Copyright (c) 2014 live Interactive. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "LFAnimatedImageView.h"

/**
 可以显示 GIF 的 Image。

 @discussion 该类和 UIImage 用法一样，可以作为 UIImage 的完整替代品。
 只有当被显示在 LFAnimatedImageView 里时，才会有动画效果。
 
 示例代码:
     // icon@2x.gif
     LFGIFImage *image = [LFGIFImage imageNamed:@"icon"];
     LFAnimatedImageView *imageView = [LFAnimatedImageView alloc] initWithImage:image];
     [view addSubView:imageView];
 */
@interface LFGIFImage : UIImage <LFAnimatedImage>

// 下面方法声明和 UIImage 一样， 只是为了避免编译警告
+ (LFGIFImage *)imageNamed:(NSString *)name; // 不再缓存
+ (LFGIFImage *)imageWithContentsOfFile:(NSString *)path;
+ (LFGIFImage *)imageWithData:(NSData *)data;
+ (LFGIFImage *)imageWithData:(NSData *)data scale:(CGFloat)scale;

@end
