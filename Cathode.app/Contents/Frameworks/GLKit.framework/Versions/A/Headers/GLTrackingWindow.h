//
//  GLTrackingWindow.h
//  GLKit
//
//  Created by Colin Caufield on 11-06-24.
//  Copyright 2011 Secret Geometry. All rights reserved.
//

#import <Cocoa/Cocoa.h>

@protocol GLTrackingWindow <NSObject>

- (NSRect) actualFrame;
- (BOOL) isTopmost;

@end

@protocol GLTrackingWindowController <NSObject>

- (NSTimeInterval) timeWhenLastMain;
- (void) windowDidReposition;

@end
