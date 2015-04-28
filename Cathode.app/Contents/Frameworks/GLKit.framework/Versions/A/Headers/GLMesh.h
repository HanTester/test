//
// Copyright 2014 Secret Geometry, Inc.  All rights reserved.
//

#import <Foundation/Foundation.h>

//
// GLMesh
//

@interface GLMesh : NSObject

- (id) initWithPositions:(GLfloat*)positions
                 normals:(GLfloat*)normals
               texcoords:(GLfloat*)texcoords
                 indices:(GLushort*)indices
             vertexCount:(int)vertexCount
              indexCount:(int)indexCount;

- (void) render;

@end
