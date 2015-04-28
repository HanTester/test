//
// Copyright 2014 Secret Geometry, Inc.  All rights reserved.
//

#import <Foundation/Foundation.h>
#import "GLMath.h"

enum TextureType
{
    RECTANGLE,
    CUBEMAP
};

enum ColorType
{
    RGBA,
    LUMINANCE
};

enum SamplingType
{
    NEAREST,
    BILINEAR,
    TRILINEAR
};

enum WrappingType
{
    CLAMP,
    REPEAT,
    MIRRORED_REPEAT
};

struct TextureOptions
{
    TextureType textureType;
    int width;
    int height;
    unsigned int sampler;
    ColorType colorType;
    SamplingType samplingType;
    WrappingType wrappingType;
    BOOL canBeRenderTarget;
};

//
// GLTexture
//

@interface GLTexture : NSObject

@property (readonly) unsigned int glName;
@property (readonly) int width;
@property (readonly) int height;
@property (readonly) vec2 size;
@property (readonly) unsigned int sampler;
@property (readonly) unsigned int maxMipLevel;

- (id) initWithNSData:(NSData*)data options:(TextureOptions*)options;
- (id) initWithNSDataArray:(NSArray*)array options:(TextureOptions*)options;

- (id) initWithNoise:(TextureOptions*)options;
- (id) initWithConstant:(uint32_t)pixel options:(TextureOptions*)options;

- (id) initWithImage:(NSImage*)image options:(TextureOptions*)options;
- (id) initWithCGImage:(CGImageRef)image options:(TextureOptions*)options;
- (id) initWithBitmap:(NSBitmapImageRep*)bitmap options:(TextureOptions*)options;

- (void) activate;
+ (void) deactivateAll;
- (void) unload;

- (void) write:(const void*)data;
- (void) write:(const void*)data at:(IntPoint)point size:(IntSize)size;

- (void) becomeRenderTarget;
- (void) resignRenderTarget;

- (int) mipLevelForSize:(IntSize)size;
- (IntSize) sizeForMipLevel:(int)level;

@end
