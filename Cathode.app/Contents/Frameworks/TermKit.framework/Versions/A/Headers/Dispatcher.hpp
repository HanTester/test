//
// Copyright (c) 2014 Secret Geometry, Inc.  All rights reserved.
//

#ifndef TERMKIT_DISPATCHER_HPP
#define TERMKIT_DISPATCHER_HPP

#include "Utilities.hpp"
#include "Types.hpp"
#include <stdint.h>

namespace term {

// 
// Dispatcher
// 

class Dispatcher
{
  public:
    
    //
    Dispatcher(Context& c);
    
    //
    void text(wchar_t c);
    
    //
    void diacritic(wchar_t d);
    
    //
    void controlChar(uint8_t c);
    
    //
    void escapeSequence(uint8_t c, const UIntVector& args);
    
    //
    void charsetSequence(uint8_t c, const UIntVector& args);
    
    //
    void lineAttributeSequence(uint8_t c);
    
    //
    void controlSequence(uint8_t c, bool questionMark, const UIntVector& args);
    
    // 
    void operatingSystemCommand(const uint8_t* command);
    
  private:
    
    Context& _context;
};

}

#endif
