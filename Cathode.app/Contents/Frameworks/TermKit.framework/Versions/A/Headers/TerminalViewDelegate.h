//
// Copyright (c) 2014 Secret Geometry, Inc.  All rights reserved.
//

//
// 
//
@protocol TerminalViewDelegate <NSObject>

@required

- (void) writeChar:(unichar)uc;
- (void) writeString:(NSString*)text;
- (void) functionKey:(int)key;
- (void) upArrowKey;
- (void) downArrowKey;
- (void) leftArrowKey;
- (void) rightArrowKey;
- (void) forwardDeleteKey;
- (void) pageUpKey;
- (void) pageDownKey;
- (void) moveWordLeft;
- (void) moveWordRight;
- (void) clearBuffer;
- (void) didResizeColumns:(NSUInteger)cols rows:(NSUInteger)rows;

@end
