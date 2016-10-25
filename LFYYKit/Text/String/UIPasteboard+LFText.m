//
//  UIPasteboard+LFText.m

//  Created by guoyaoyuan on 15/4/2.
//  
//
//  This source code is licensed under the MIT-style license found in the
//  LICENSE file in the root directory of this source tree.
//

#import "UIPasteboard+LFText.h"
#import "NSAttributedString+LFText.h"
#import "LFGIFImage.h"
#import <MobileCoreServices/MobileCoreServices.h>

NSString *const LFPasteboardTypeAttributedString = @"com.laifeng.NSAttributedString";
NSString *const LFUTTypeWEBP = @"com.google.webp";

@implementation UIPasteboard (LFText)


- (void)setPNGData:(NSData *)PNGData {
    [self setData:PNGData forPasteboardType:(id)kUTTypePNG];
}

- (NSData *)PNGData {
    return [self dataForPasteboardType:(id)kUTTypePNG];
}

- (void)setJPEGData:(NSData *)JPEGData {
    [self setData:JPEGData forPasteboardType:(id)kUTTypeJPEG];
}

- (NSData *)JPEGData {
    return [self dataForPasteboardType:(id)kUTTypeJPEG];
}

- (void)setGIFData:(NSData *)GIFData {
    [self setData:GIFData forPasteboardType:(id)kUTTypeGIF];
}

- (NSData *)GIFData {
    return [self dataForPasteboardType:(id)kUTTypeGIF];
}

- (void)setWEBPData:(NSData *)WEBPData {
    [self setData:WEBPData forPasteboardType:LFUTTypeWEBP];
}

- (NSData *)WEBPData {
    return [self dataForPasteboardType:LFUTTypeWEBP];
}

- (void)setImageData:(NSData *)imageData {
    [self setData:imageData forPasteboardType:(id)kUTTypeImage];
}

- (NSData *)imageData {
    return [self dataForPasteboardType:(id)kUTTypeImage];
}

- (void)setAttributedString:(NSAttributedString *)attributedString {
    self.string = [attributedString plainTextForRange:NSMakeRange(0, attributedString.length)];
    NSData *data = [attributedString archiveToData];
    if (data) {
        NSDictionary *item = @{LFPasteboardTypeAttributedString : data};
        [self addItems:@[item]];
    }
    [attributedString enumerateAttribute:LFTextAttachmentAttributeName inRange:NSMakeRange(0, attributedString.length) options:NSAttributedStringEnumerationLongestEffectiveRangeNotRequired usingBlock:^(LFTextAttachment *attachment, NSRange range, BOOL *stop) {
        UIImage *img = attachment.content;
        if ([img isKindOfClass:[UIImage class]]) {
            NSDictionary *item = @{@"com.apple.uikit.image" : img};
            [self addItems:@[item]];
        }
    }];
}

- (NSAttributedString *)attributedString {
    for (NSDictionary *items in self.items) {
        NSData *data = items[LFPasteboardTypeAttributedString];
        if (data) {
            return [NSAttributedString unarchiveFromData:data];
        }
    }
    return nil;
}

@end
