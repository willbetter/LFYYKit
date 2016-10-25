//
//  LFSentinel.m

//  Created by guoyaoyuan on 15/4/13.
//  
//
//  This source code is licensed under the MIT-style license found in the
//  LICENSE file in the root directory of this source tree.
//

#import "LFSentinel.h"
#import <libkern/OSAtomic.h>

@implementation LFSentinel {
    int32_t _value;
}

- (int32_t)value {
    return _value;
}

- (int32_t)increase {
    return OSAtomicIncrement32(&_value);
}

@end
