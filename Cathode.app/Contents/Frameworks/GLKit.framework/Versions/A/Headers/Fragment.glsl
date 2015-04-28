//
// Copyright 2014 Secret Geometry, Inc.  All rights reserved.
//

#ifndef FRAGMENT_GLSL
#define FRAGMENT_GLSL

#include <Utilities.glsl>

//#define ONLY_SHOW_COLORS
//#define ONLY_SHOW_NORMALS
//#define ONLY_SHOW_OCCLUSION

#define SEE(value) {gl_FragColor = vec4(value); return;}

// Uniforms.
uniform vec4  color;
uniform float shininess;
uniform float lightLevel;

// Varyings.
varying vec4  userSpacePos;
varying vec4  objSpacePos;
varying vec4  worldSpacePos;
varying vec3  worldSpaceNormal;

// Constants.
const vec3  LIGHT_POS             = vec3(0.0, 1000.0, 300.0 - 5000.0);
const vec3  LIGHT_COLOR           = vec3(0.4);
const vec3  AMBIENT_LIGHT_COLOR   = vec3(0.6);
const float AMBIENT_OCCLUSION_EXP = 8.0;
const float IMAGE_KEY             = 0.05;
const float MIDZONE_LUMINANCE     = 0.18;
const float WHITE_LUMINANCE       = 1.00;

// Globals.
vec3  normal;
vec3  lightVec;
vec3  eyeVec;
vec3  halfVec;
float normalDotLight;
float normalDotEye;
float normalDotHalf;

// Functions.

void calculateVectors(vec3 normalDir)
{
    normal         = normalize(normalDir);
    lightVec       = normalize(LIGHT_POS - worldSpacePos.xyz);
    eyeVec         = normalize(vec3(0.0) - worldSpacePos.xyz);
    halfVec        = normalize(lightVec + eyeVec);
    normalDotLight = max(0.0, dot(normal, lightVec));
    normalDotEye   = max(0.0, dot(normal, eyeVec));
    normalDotHalf  = max(0.0, dot(normal, halfVec));
}

void draw(vec4 color, float shininess, float occlusion, float shadow, vec3 reflection, vec3 emissive)
{
    #ifdef ONLY_SHOW_COLORS
        gl_FragColor = color;
        return;
    #endif
    
    #ifdef ONLY_SHOW_NORMALS
        gl_FragColor = vec4(normal, 1.0);
        return;
    #endif
    
    #ifdef ONLY_SHOW_OCCLUSION
        gl_FragColor = vec4(vec3(occlusion), 1.0);
        return;
    #endif
    
    vec3 ambient = (1.0 - occlusion) * color.rgb * AMBIENT_LIGHT_COLOR;
    
    vec3 diffuse = (1.0 - shadow) * normalDotLight * color.rgb * LIGHT_COLOR;
    
    vec3 specular = (1.0 - shadow) * pow(normalDotHalf, shininess) * WHITE * LIGHT_COLOR;
    
    vec3 litColor = (
         ambient +
         diffuse +
         specular +
         reflection
         ) * lightLevel + emissive;
    
    gl_FragColor = vec4(litColor, color.a);
}

#endif // FRAGMENT_GLSL
