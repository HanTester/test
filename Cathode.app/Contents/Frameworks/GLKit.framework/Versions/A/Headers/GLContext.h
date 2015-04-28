//
// Copyright 2014 Secret Geometry, Inc.  All rights reserved.
//

#import <Foundation/Foundation.h>
#import "GLMath.h"
#import "GLShader.h"
#import "GLTexture.h"

//
// GLContext
//

@interface GLContext : NSObject

@property (nonatomic, strong) GLShader* basicShader;
@property (nonatomic, strong) GLShader* currentShader;
@property (nonatomic) BOOL useDepth;
@property (nonatomic) BOOL backfaceCulling;
@property (nonatomic) BOOL wireframe;

- (id) initWithCocoaContext:(NSOpenGLContext*)cc;
- (void) activate;
- (void) push;
- (void) pop;
- (void) removeMatrices;
- (void) restoreMatrices;
- (void) loadIdentity;
- (void) translate:(vec3)translation;
- (void) rotate:(vec2)rotation;
- (void) scale:(vec3)scale;
- (void) clear;
- (void) clear:(vec4)color;
- (const mat4&) modelViewMatrix;
- (void) setModelViewMatrix:(const mat4&)matrix;

- (void) renderTexture:(GLTexture*)tex frame:(NSRect)frame viewSize:(NSSize)viewSize;
- (void) renderFullviewTexture:(GLTexture*)tex;
- (void) renderFullviewTexture:(GLTexture*)tex scale:(vec2)scale;
- (void) renderFullviewRect;
- (void) renderOrthoRect:(NSRect)rect;

- (void) renderTriangle:(tri)aTri color:(vec3)color alpha:(float)alpha;
- (void) renderQuad:(quad)aQuad color:(vec3)color alpha:(float)alpha;
- (void) renderBox:(aabb)box color:(vec3)color alpha:(float)alpha;

- (void) renderSphereWithRadius:(float)radius color:(vec3)color alpha:(float)alpha;
- (void) renderCubeWithSize:(float)size color:(vec3)color alpha:(float)alpha;

- (void) renderCone:(float)size;
- (void) renderTorus:(float)size;
- (void) renderDodecahedron:(float)size;
- (void) renderOctahedron:(float)size;
- (void) renderTetrahedron:(float)size;
- (void) renderIcosahedron:(float)size;
- (void) renderTeapot:(float)size;

+ (void) lockGL;
+ (void) unlockGL;
+ (void) checkForErrors;

@end
