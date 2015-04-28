//
// Copyright 2014 Secret Geometry, Inc.  All rights reserved.
//

#import <Foundation/Foundation.h>
#import "GLMath.h"

@class GLProgram, GLTexture;


@interface GLShader : NSObject

@property (nonatomic, copy) NSString* name;
@property (nonatomic, strong) GLProgram* program;
@property (nonatomic, strong) NSMutableArray* defines;

- (id) initWithName:(NSString*)name;
- (void) activate;
+ (void) deactivateAll;
+ (void) reloadAll;
- (void) recompile;
- (void) setFloat:(float)value forName:(NSString*)name;
- (void) setVec2:(vec2)value forName:(NSString*)name;
- (void) setVec3:(vec3)value forName:(NSString*)name;
- (void) setVec4:(vec4)value forName:(NSString*)name;
- (void) setBool:(BOOL)value forName:(NSString*)name;
- (void) setInt:(int)value forName:(NSString*)name;
- (void) setIVec2:(ivec2)value forName:(NSString*)name;
- (void) setTexture:(GLTexture*)tex forName:(NSString*)name;

@end
