//
//  GLRenderer.h
//  GLKit
//
//  Created by Colin Caufield on 12-03-11.
//  Copyright (c) 2014 Secret Geometry. All rights reserved.
//

#import <Foundation/Foundation.h>

@class GLContext, GLView;

@interface GLRenderer : NSObject

@property (nonatomic, strong) GLContext* context;
@property (nonatomic, strong) GLView* view;

- (id) initWithContext:(GLContext*)context view:(GLView*)view;
- (void) update:(NSTimeInterval)seconds;
- (void) render;
- (void) overlay;

@end
