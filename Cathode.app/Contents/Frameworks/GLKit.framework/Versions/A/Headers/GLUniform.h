//
// Copyright 2014 Secret Geometry, Inc.  All rights reserved.
//

#import <Foundation/Foundation.h>
#import "GLMath.h"

@class GLTexture;


@interface GLUniform : NSObject <NSCopying>

@property (copy) NSString* name;
@property int location;
@property int modificationCount;

- (id) initWithName:(NSString*)name location:(int)location;
- (void) copyValueFrom:(GLUniform*)other;
- (void) bind;
- (NSString*) description;

@end


@interface GLFloatUniform : GLUniform

@property (nonatomic) float value;

@end


@interface GLVec2Uniform : GLUniform
{
    float value[2];
}

@property (nonatomic) vec2 value;

@end


@interface GLVec3Uniform : GLUniform
{
    float value[3];
}

@property (nonatomic) vec3 value;

@end


@interface GLVec4Uniform : GLUniform
{
    float value[4];
}

@property (nonatomic) vec4 value;

@end


@interface GLTextureUniform : GLUniform
{
    GLTexture* value;
}

@property (nonatomic, strong) GLTexture* value;

@end
