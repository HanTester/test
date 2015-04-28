//
// Copyright 2014 Secret Geometry, Inc.  All rights reserved.
//

#import <Foundation/Foundation.h>


@interface GLProgram : NSObject

@property (nonatomic, copy) NSString* name;
@property (nonatomic, strong) NSArray* defines;
@property (nonatomic, strong) NSDictionary* uniforms;
@property (nonatomic, strong) NSString* vertexSource;
@property (nonatomic, strong) NSString* fragmentSource;

+ (GLProgram*) programNamed:(NSString*)name;
+ (GLProgram*) programNamed:(NSString*)name defines:(NSArray*)defs;

- (void) activate;
- (void) reload;
+ (void) reloadAll;

@end
