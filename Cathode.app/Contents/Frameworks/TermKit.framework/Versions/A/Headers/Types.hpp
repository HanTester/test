//
// Copyright (c) 2014 Secret Geometry, Inc.  All rights reserved.
//

#ifndef TERMKIT_TYPES_HPP
#define TERMKIT_TYPES_HPP

#include "Debug.hpp"
#include <stdint.h>
#include <vector>
#include <set>
#include <map>
#include <ostream>

namespace term {

class StyledChar;
class TextArea;
class Context;
class Dispatcher;
class Parser;
class Pty;

//
// Some handy STL container types.
//
typedef std::set<int>                      IntSet;
typedef std::set<unsigned int>             UIntSet;
typedef std::set<uint8_t>                  UInt8Set;
typedef std::vector<int>                   IntVector;
typedef std::vector<unsigned int>          UIntVector;
typedef std::vector<uint8_t>               UInt8Vector;
typedef std::vector<std::string>           StringVector;
typedef std::map<std::string, std::string> StringMap;

//
// A string containing a single escape character.  Used at the beginning of escape sequences.
//
#define ESC_STRING "\x1b"

//
// An escape character followed by a right square bracket.  Used at the beginning of control sequences.
//
#define CSI_PREFIX_STRING "\x1b["

//
// TermKit uses these callbacks to request actions from the host application.
//
typedef void (*BeepCallback)();
typedef void (*ResizeCallback)(Context*, size_t, size_t);

//
// 
//
enum ConnectionState
{
    ConnectionState_Disconnected,
    ConnectionState_Connecting,
    ConnectionState_Connected,
    ConnectionState_Suspended
};

//
// The VT220 spec defines a number of modes that change the terminal's behavior.
// Each mode can be ON or OFF.
// See Context::enableMode and Context::disableMode.
//
enum Mode
{
    COLUMN = 3,
    INSERT = 4,
    ORIGIN = 6,
    AUTO_WRAP = 7,
    CURSOR_BLINK = 12,
    LINE_FEED = 20,
    CURSOR_VISIBLE = 25,
    AUTO_REVERSE_WRAP = 45,
    ALT_SCREEN_BUFFER = 47,
    ALT_SCREEN_BUFFER_AND_CLEAR = 1049
};

//
// Ways to erase characters within a single line.
// See Context::eraseInLine.
//
enum EraseInLineMode
{
    CURSOR_TO_FAR_RIGHT,
    FAR_LEFT_TO_CURSOR,
    ENTIRE_LINE
};

//
// Ways to erase characters in the entire text area.
// See Context::eraseInDisplay.
//
enum EraseInDisplayMode
{
    CURSOR_TO_END,
    BEGINNING_TO_CURSOR,
    ENTIRE_GRID
};

//
// Types of requests the underlying program can make.
//
enum Request
{
    NO_REQUEST,
    DEVICE_ATTRIBUTES_REQUEST,
    CURSOR_POSITION_REQUEST
};

//
// Simple pair for describing locations in 2d data structures.
//
template <typename T>
struct Pair
{
    T x, y;
    
    Pair() : x(0), y(0) {}
    
    Pair(T i, T j) : x(i), y(j) {}
    
    bool operator==(const Pair& other) const
    {
        return x == other.x && y == other.y;
    }
    
    bool operator!=(const Pair& other) const
    {
        return x != other.x || y != other.y;
    }
    
    friend std::ostream& operator<<(std::ostream& stream, const Pair& loc)
    {
        stream << "(" << loc.x << ", " << loc.y << ")";
        return stream;
    }
};

typedef Pair<int> GridSize;
typedef Pair<int> GridLocation;
typedef Pair<int> LineLocation;

}

#endif
