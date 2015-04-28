//
//  GLInterpolator.h
//  GLKit
//
//  Created by Colin Caufield on 2014-08-31.
//  Copyright (c) 2014 Secret Geometry. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "GLMath.h"


@interface GLInterpolator : NSObject

@property (nonatomic) float smoothLevel;

@property (nonatomic) vec2 position;
@property (nonatomic) vec2 velocity;
@property (nonatomic) vec2 acceleration;

- (void) update:(NSTimeInterval)seconds;
- (void) addValue:(vec2)pos;

@end
