//
// Copyright (c) 2014 Secret Geometry, Inc.  All rights reserved.
//

#import <Foundation/Foundation.h>
#import "TerminalViewDelegate.h"

@class TerminalView;

extern NSString* const TerminalTextDidChangeNotification;


//
//
//
@interface TerminalController : NSObject <TerminalViewDelegate>

@property (nonatomic, strong) IBOutlet TerminalView* terminalView;
@property (readonly) NSString* descriptiveTitle;
@property (readonly) NSString* terminalIdentifier;
@property (readonly) NSUInteger terminalIndex;
@property (readonly) NSUInteger processCount;
@property (readonly) NSString* activeProcessName;
@property (readonly) NSArray* allProcessNames;

- (void) resetInDirectory:(NSString*)path;
- (void) updateTerminal:(id)sender;
- (void) startTimer;
- (void) stopTimer;

@end
