//
// Copyright (c) 2014 Secret Geometry, Inc.  All rights reserved.
//

#import <Cocoa/Cocoa.h>
#import "Constants.h"

@protocol TerminalViewDelegate;

//
// 
//
@interface TerminalView : NSTextView <NSTextViewDelegate>

@property (nonatomic, weak) IBOutlet id <TerminalViewDelegate> terminalDelegate;
@property (nonatomic, strong) NSFont* terminalFont;
@property (nonatomic, strong) NSFont* boldTerminalFont;
@property (nonatomic, strong) NSColor* foregroundColor;
@property (nonatomic, strong) NSColor* cursorColor;
@property (nonatomic, strong) NSColor* selectionColor;
@property (nonatomic) CGSize glyphSize;
@property (nonatomic) CursorShape cursorShape;
@property (nonatomic) BOOL shouldAntiAlias;
@property (nonatomic) BOOL useOptionAsMeta;
@property (nonatomic) BOOL deleteSendsControlH;
@property (nonatomic) BOOL copyOnSelect;
@property (nonatomic) BOOL middleClickPaste;

// Clears everything except the most recent line.
- (IBAction) clearBuffer:(id)sender;

//
- (void) write:(NSString*)string;

//
- (void) updateBlink:(id)sender;

//
- (void) scrollToBottom;

// 
- (BOOL) isScrolledNearBottom;

@end
