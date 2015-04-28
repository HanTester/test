//
// Copyright (c) 2014 Secret Geometry, Inc.  All rights reserved.
//

#ifndef TERMKIT_CONTEXT_HPP
#define TERMKIT_CONTEXT_HPP

#include "TextArea.hpp"
#include "Types.hpp"
#include "Rect.hpp"
#include "Utilities.hpp"

namespace term {

// 
// Context
//
// A context
// 

class Context
{
  public:
    
    //
    Context(size_t width, size_t height, size_t maxLines, BeepCallback beepFunc, ResizeCallback resizeFunc);
    
    // Return to starting state.
    void reset();
    
    // Removes all text, except for the most recent line.
    void clearBuffer();
    
    // Fill the grid with the letter 'E'.  This is a standard test in the VT220 spec.
    void fillWithTestPattern();
    
    // Set the grid's dimensions.
    void setColumnCount(size_t cols);
    void setRowCount(size_t rows);
    
    void resize(size_t width,
                size_t height,
                bool shouldCallback = false,
                bool moveMargins = true,
                bool moveCursor = true);
    
    // Set the user-visible title.
    void setTitle(const char* title);
    
    // Beep.
    void bell();
    
    //
    TextArea& textArea();
    const TextArea& textArea() const;
    
    //
    size_t bufferIndex() const;
    
    // Write text at the current cursor position, and advance the cursor.  Wraps will happen if autowrap is enabled.
    void echo(const wchar_t* s, size_t length);
    void echo(wchar_t c);
    
    // Add an accent to the cell *before* the cursor.
    void addDiacritic(wchar_t diacritic);
    
    // 
    void setUseLineDrawingCharacters(bool b);
    
    GridLocation cursorLoc() const;
    void setCursorLoc(GridLocation c);
    
    bool showCursor();
    
    // Manage the cursor stack.
    void saveCursor();
    void restoreCursor();
    
    // Move the cursor, if possible.
    void moveCursorUp(size_t n = 1);
    void moveCursorDown(size_t n = 1);
    void moveCursorLeft(size_t n = 1);
    void moveCursorRight(size_t n = 1);
    void moveCursorForward();
    void moveCursorBackward();
    void moveCursorToFarLeft();
    void moveCursorToNextTabStop();
    void moveCursorToRowCol(size_t row, size_t col);
    
    // Move the cursor and scroll when the margins are reached.
    void pushCursorUp();
    void pushCursorDown();
    void pushCursorToNewLine();
    void pushCursorToFirstColOfNewLine();
    
    // Sets the margins inside of which scrolling happens.
    // The parameters are 1-indexed and should conform to (1 <= top < bottom <= height).
    // Out of range values will be clamped.
    void setTopAndBottomMargins(size_t top, size_t bottom);
    
    void scrollUp(size_t n = 1);
    void scrollDown(size_t n = 1);
    
    // Set the color and style that will be used when writing characters.
    // The args array can contain multiple settings (eg. blue and underline).  See the VT220 specs for details.
    void selectGraphicRendition(const UIntVector& args);
    
    // Erases characters in the current line using the given mode.
    void eraseInLine(EraseInLineMode mode);
    
    // Erases characters in the entire text area using the given mode.
    void eraseInDisplay(EraseInDisplayMode mode);
    
    // Erases the given number of characters without moving the cursor.
    void eraseCharacters(size_t count);
    
    // Deletes a single character behind the cursor.  All subsequent characters will be shifted backward. 
    void deleteBackwards();
    
    //
    void insertBlankCharacters(size_t count);
    
    // Deletes characters in the current line.
    void deleteCharacters(size_t count);
    
    // 
    void insertLines(size_t count);
    
    // 
    void deleteLines(size_t count);
    
    //
    void setTabStop();
    void clearTabStop();
    void clearAllTabStops();
    
    // Enable/disable the given mode.
    void enableMode(const UIntVector& modes, bool questionMark);
    void disableMode(const UIntVector& modes, bool questionMark);
    
    void setBackgroundColorErase(bool on);
    
    // Requests a terminal identification string.
    void requestDeviceAttributes();
    
    // Requests the terminal's status.
    void requestDeviceStatusReport(int type);
    
    // Query the response for the last request made.
    const char* getResponse();
    
    //
    const RectVector& dirtyRects() const;
    
    //
    const Rect& giantDirtyRect() const;
    
    //
    void clearDirtyRects();
    
    //
    void sanityCheck();
    
  private:
    
    void scrollUp(size_t top, size_t bottom, size_t rowCount);
    void scrollDown(size_t top, size_t bottom, size_t rowCount);
    void addDirtyRect(const Rect& rect);
    void markAllRectsDirty();
    wchar_t convertToLineDrawingCharacter(wchar_t c);
    
    TextArea       _textArea0;
    TextArea       _textArea1;
    TextArea*      _textArea;
    GridLocation   _cursor;
    GridLocation   _backupCursor;
    StyledChar     _prototypeChar;
    StyledChar     _backupPrototypeChar;
    size_t         _topMargin;
    size_t         _bottomMargin;
    UIntSet        _tabStops;
    RectVector     _dirtyRects;
    Rect           _giantDirtyRect;
    bool           _insert;
    bool           _autoWrap;
    bool           _autoReverseWrap;
    bool           _originMode;
    bool           _wideColumnMode;
    bool           _lineFeedCarriageReturn;
    bool           _useLineDrawingCharacters;
    bool           _needsWrap;
    bool           _backgroundColorErase;
    bool           _showCursor;
    BeepCallback   _beepCallback;
    ResizeCallback _resizeCallback;
    Request        _request;
    std::string    _response;
};

}

#endif
