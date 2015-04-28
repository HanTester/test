//
// Copyright 2014 Secret Geometry, Inc.  All rights reserved.
//

#ifndef VERTEX_GLSL
#define VERTEX_GLSL

varying vec4 userSpacePos;
varying vec4 objSpacePos;
varying vec4 worldSpacePos;
varying vec3 worldSpaceNormal;

void transform(vec4 position, vec3 normalDir)
{
    userSpacePos      = gl_Vertex;
    objSpacePos       = position;
    worldSpacePos     = gl_ModelViewMatrix * position;
    worldSpaceNormal  = normalize(gl_NormalMatrix * normalDir);
    gl_Position       = gl_ModelViewProjectionMatrix * position;
}

#endif // VERTEX_GLSL
