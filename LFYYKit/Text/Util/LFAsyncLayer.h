//
//  LFAsyncLayer.h

//  Created by guoyaoyuan on 15/4/11.
//  
//
//  This source code is licensed under the MIT-style license found in the
//  LICENSE file in the root directory of this source tree.
//

#import <UIKit/UIKit.h>
#import <QuartzCore/QuartzCore.h>

@class LFAsyncLayerDisplayTask;


/**
 The LFAsyncLayer class is a subclass of CALayer used for render contents asynchronously.
 
 @discussion When the layer need update it's contents, it will ask the delegate 
 for a async display task to render the contents in a background queue.
 */
@interface LFAsyncLayer : CALayer
/// Whether the render code is executed in background. Default is YES.
@property BOOL displaysAsynchronously;
@end


/**
 The LFAsyncLayer's delegate protocol. The delegate of the LFAsyncLayer (typically a UIView)
 must implements the method in this protocol.
 */
@protocol LFAsyncLayerDelegate <NSObject>
@required
/// This method is called to return a new display task when the layer's contents need update.
- (LFAsyncLayerDisplayTask *)newAsyncDisplayTask;
@end


/**
 A display task used by LFAsyncLayer to render the contents in background queue.
 */
@interface LFAsyncLayerDisplayTask : NSObject

/**
 This block will be called before the asynchronous drawing begins.
 It will be called on the main thread.
 
 param layer  The layer.
 */
@property (nonatomic, copy) void (^willDisplay)(CALayer *layer);

/**
 This block is called to draw the layer's contents.
 
 @discussion This block may be called on main thread or background thread,
 so is should be thread-safe.
 
 param context      A new bitmap content created by layer.
 param size         The content size (typically same as layer's bound size).
 param isCancelled  If this block returns `YES`, the method should cancel the
 drawing process and return as quickly as possible.
 */
@property (nonatomic, copy) void (^display)(CGContextRef context, CGSize size, BOOL(^isCancelled)(void));

/**
 This block will be called after the asynchronous drawing finished.
 It will be called on the main thread.
 
 param layer  The layer.
 param finished  If the draw process is cancelled, it's `NO`, otherwise it's `YES`;
 */
@property (nonatomic, copy) void (^didDisplay)(CALayer *layer, BOOL finished);

@end
