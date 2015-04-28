//
// Copyright (c) 2014 Secret Geometry, Inc.  All rights reserved.
//

#ifndef TERMKIT_TEXTAREA_HPP
#define TERMKIT_TEXTAREA_HPP

#include "StyledChar.hpp"
#include "Types.hpp"
#include "Utilities.hpp"

namespace term {

class TextAreaImplementation;

/*
 
 TextArea

- A two dimensional data structure that holds elements of type StyledChar.
- StyledChars can be accessed by column (x) and row (y) using a GridLocation.
- GridLocation(0, 0) is at the top left of the active area
- A TextArea can be modified with methods for writing, erasing, copying, filling, and resizing.
- Text shifted above the active area has a negative y value.
- Can be dynamically resized and will reflow and shift text as needed.
- Internally, text is stored as a list of StyledStrings, accessed using a LineLocation struct.
- New lines can be added, in which case previous lines are shifted upwards.
- Lines are remembered after they are shifted out of view.  After a user defined amount, lines will be dropped.
- The oldest saved line starts at LineLocation(0, 0).
*/

class TextArea
{
  public:
    
    //
    TextArea(size_t width, size_t height, size_t maxLines);
    
    //
    ~TextArea();
    
    // 
    size_t width() const;
    
    //
    size_t height() const;
    
    //
    size_t activeLines() const;
    
    //
    size_t totalLines() const;
    
    //
    size_t droppedLines() const;
    
    //
    size_t totalRows();
    
    //
    void setSize(size_t newWidth, size_t newHeight, int preserveRowsUpTo = -1);
    
    //
    void setLineCapacity(size_t newCapacity);
    
    //
    void appendEmptyLines(size_t numLines, StyledChar* clearChar = nullptr);
    
    //
    void insertLine(int lineIndex, const StyledString& line);
    
    //
    void clearAllLines();
    
    //
    void clearActiveRows();
    
    //
    void removeAllLines();
    
    // 
    const StyledString& lineForIndex(int lineIndex) const;
    
    // 
    const StyledString& lineForRow(int row);
    
    // Returns [0, 0].
    GridLocation topLeft() const;
    
    // Returns [width - 1, height - 1].
    GridLocation bottomRight() const;
    
    // Returns [width, height - 1].
    GridLocation bottomRightEnd() const;
    
    // Returns a new grid location shifted by the given offset, positive or negative, and wrapping as needed.
    GridLocation gridLocationByShifting(GridLocation loc, int offset) const;
    
    //
    LineLocation lastLineEnd() const;
    
    // Returns the number of rows required for a string of the given length.
    // An empty string has a height of 1.
    size_t heightForLength(size_t length) const;
    
    //
    int distanceBetweenGridLocations(GridLocation a, GridLocation b);
    
    // 
    bool gridLocationIsValid(GridLocation loc);
    
    // 
    bool lineIndexIsValid(int index) const;
    
    //
    LineLocation lineLocForGridLoc(GridLocation gridLoc);
    GridLocation gridLocForLineLoc(LineLocation lineLoc);
    
    //
    StyledChar read(GridLocation c);
    
    //
    void write(GridLocation loc, const StyledChar& value);
    
    //
    void insert(GridLocation loc, const StyledChar& value);
    
    //
    void remove(GridLocation begin, GridLocation end);
    
    //
    void clear(GridLocation begin, GridLocation end);
    
    //
    void fill(GridLocation begin, GridLocation end, const StyledChar& value = StyledChar());
    
    //
    void shift(int beginRow, int endRow, int offset, StyledChar* clearChar = nullptr);
    
    //
    void split(int row);
    
    //
    void join(int row);
    
    //
    void sanityCheck();
    
    //
    void printLines();
    
  private:
    
    int calculateTotalRows();
    void recalculateLayout();
    void calculateMappingBackToLine(int line);
    void calculateMappingBackToRow(int row);
    void calculateMappingBackToRowOrLine(int row, int line);
    void insertLinesAtIndex(int lineIndex, int count, const StyledString& str);
    void eraseLines(int beginIndex, int endIndex);
    
    size_t                    _width;
    size_t                    _height;
    size_t                    _maxLines;
    size_t                    _droppedLines;
    size_t                    _activeLines;
    size_t                    _activeRows;
    size_t                    _totalRows;
    std::vector<LineLocation> _bottomUpRowToLineMap;
    std::vector<GridLocation> _bottomUpLineToRowMap;
    TextAreaImplementation*   _implementation;
};

}

#endif // TERMKIT_TEXTAREA_HPP
