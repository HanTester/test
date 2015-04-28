//
//  GLUtilities.h
//  GLKit
//
//  Created by Colin Caufield on 11-06-24.
//  Copyright 2011 Secret Geometry. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "GLMath.h"
#include <vector>

#define RETURN_OR_ASSIGN(a, b) if (a == b) return; else a = b;
#define RETURN_OR_RETAIN(a, b) if (a == b) return; else {[a release]; a = [b retain];}
#define RETURN_OR_COPY(a, b)   if (a == b) return; else {[a release]; a = [b copy];}

void ExitGracefully(NSString* message);

bool operator==(const NSRange& a, const NSRange& b);
bool operator==(const NSPoint& a, const NSPoint& b);
bool operator==(const NSSize& a, const NSSize& b);
bool operator==(const NSRect& a, const NSRect& b);

NSPoint Vec2ToPoint(vec2 vec);
vec2 PointToVec2(NSPoint point);

NSSize Vec2ToSize(vec2 vec);
vec2 SizeToVec2(NSSize point);

NSSize IVec2ToSize(ivec2 vec);
ivec2 SizeToIVec2(NSSize size);

NSArray* Vec3ToArray(vec3 vec);
vec3 ArrayToVec3(NSArray* array);

NSColor* Vec3ToColor(vec3 vec);
vec3 ColorToVec3(NSColor* color);

NSColor* Vec4ToColor(vec4 vec);
vec4 ColorToVec4(NSColor* color);

template <typename T, int N>
NSData* CArrayToData(T (&array)[N])
{
    unsigned long length = N * sizeof(T);
    return [NSData dataWithBytesNoCopy:array length:length freeWhenDone:NO];
}

template <typename T>
NSData* VectorToData(std::vector<T>& vec)
{
    unsigned long length = vec.size() * sizeof(T);
    return [NSData dataWithBytesNoCopy:&vec[0] length:length freeWhenDone:NO];
}
