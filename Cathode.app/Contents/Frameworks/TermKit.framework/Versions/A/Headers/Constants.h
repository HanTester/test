//
//  Constants.h
//  TermKit
//
//  Created by Colin Caufield on 7/19/14.
//

#import <Foundation/Foundation.h>

typedef enum
{
    BlockCursorShape = 0,
    UnderlineCursorShape = 1,
    VerticalLineCursorShape = 2
}
CursorShape;

#define DEFAULTS NSUserDefaults.standardUserDefaults

// NSUserDefaults keys.

extern NSString* const TermKitBackgroundColor;
extern NSString* const TermKitCopyOnSelect;
extern NSString* const TermKitCursorColor;
extern NSString* const TermKitCursorShape;
extern NSString* const TermKitDeleteSendsControlH;
extern NSString* const TermKitFont;
extern NSString* const TermKitForegroundColor;
extern NSString* const TermKitMiddleClickPaste;
extern NSString* const TermKitSelectionColor;
extern NSString* const TermKitShouldAntiAlias;
extern NSString* const TermKitTerminalIdentifier;
extern NSString* const TermKitUseOptionAsMeta;
extern NSString* const TermKitInitialDirectory;

// NSAttributedString custom attributes.

extern NSString* const UserColorAttributeName;
extern NSString* const CursorAttributeName;
extern NSString* const BlinkAttributeName;
