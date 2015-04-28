//
// Copyright (c) 2014 Secret Geometry, Inc.  All rights reserved.
//

#ifndef TERMKIT_STYLEDCHAR_HPP
#define TERMKIT_STYLEDCHAR_HPP

#include "Types.hpp"
#include <iostream>

namespace term {

class StyledChar
{
  public:
    
    StyledChar(wchar_t c = '\0')
    :
        character(c)
    {
        resetStyle();
    }
    
    void resetStyle()
    {
        fgColor = 15; // white
        bgColor = 0; // black
        bold = false;
        reverse = false;
        underscore = false;
        blink = false;
        dim = false;
    }
    
    bool operator==(const StyledChar& other) const
    {
        return character == other.character;
    }
    
    friend std::ostream& operator<<(std::ostream& stream, const StyledChar& c)
    {
        stream << char(c.character);
        return stream;
    }
    
    wchar_t character;
    uint8_t fgColor;
    uint8_t bgColor;
    bool bold:1;
    bool reverse:1;
    bool underscore:1;
    bool blink:1;
    bool dim:1;
};

typedef std::vector<StyledChar> StyledString;
    
inline std::ostream& operator<<(std::ostream& stream, const StyledString& s)
{
    for (auto& c : s)
        stream << c;
    
    return stream;
}

}

#endif
