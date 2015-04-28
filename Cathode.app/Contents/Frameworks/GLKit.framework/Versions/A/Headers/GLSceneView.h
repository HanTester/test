//
// Copyright 2014 Secret Geometry, Inc.  All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import "GLView.h"
#import "GLTypes.h"
#import "GLShader.h"
#import "GLMath.h"
#import "GLInterpolator.h"


@interface GLSceneView : GLView

// Camera
@property (nonatomic) float cameraDistance;
@property (nonatomic) vec2 cameraOffset;
@property (nonatomic) vec2 centerOffset;
@property (nonatomic) ProjectionType projectionType;

// Transform
@property (nonatomic) vec2 actualFrameOrigin;
@property (nonatomic) vec2 actualFrameSize;
@property (nonatomic) vec2 originOffset;
@property (nonatomic) vec2 monitorRotation;
@property (nonatomic) mat4 modelViewMatrix;
//@property (nonatomic, strong) GLInterpolator* movement;

// Light
@property (nonatomic) vec3 lightPos;
@property (nonatomic) vec3 lightColor;
@property (nonatomic) float lightLevel;

// Options
@property (nonatomic) vec4 clearColor;
@property (nonatomic) BOOL showAxes;
@property (nonatomic) BOOL showBoundingBox;
@property (nonatomic) BOOL mouseControlsCamera;

// Callbacks
- (void) transformWasChanged;
- (void) lightingWasChanged;

// Camera
- (void) resetCamera;
- (void) moveCamera:(float)amount;
- (void) offsetCamera:(vec2)offset;
- (void) rotateCamera:(vec2)radians;

// Shaders
- (void) addLitShader:(GLShader*)shader;
- (void) removeLitShader:(GLShader*)shader;

// 
- (void) transform;

//
- (void) renderScene;

//
- (IBAction) resetCamera:(id)sender;

@end
