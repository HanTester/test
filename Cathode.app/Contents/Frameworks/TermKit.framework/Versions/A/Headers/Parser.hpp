//
// Copyright (c) 2014 Secret Geometry, Inc.  All rights reserved.
//

#ifndef TERMKIT_PARSER_HPP
#define TERMKIT_PARSER_HPP

#include "Dispatcher.hpp"
#include "Utilities.hpp"

namespace term {

// 
// Parser
//
// A parser takes a stream of raw bytes and combines them into sequences as defined by the VT220 spec.
// There are many types of sequences, including text, escape sequences, control sequences, etc.
// Completed sequences are handed off to a Dispatcher instance.
// Partial sequences are remembered between calls to parse(...).
// All plain text is interpretted as UTF-8/Unicode.
// 

class Parser
{
  public:
    
    Parser(Dispatcher& d);
    
    void parse(const uint8_t* str, size_t count);
    void parse(uint8_t c);
    
  private:
    
    void parseTextChar(uint8_t c);
    void parseUnicodeTextChar(uint8_t c);
    void parseEscapeSequenceChar(uint8_t c);
    void parseCharacterSetSequenceChar(uint8_t c);
    void parseLineAttributeSequenceChar(uint8_t c);
    void parseControlSequenceChar(uint8_t c);
    void parseOperatingSystemCommandChar(uint8_t c);
    
    void logChar(uint8_t c);
    
    Dispatcher& _dispatcher;
    UIntVector  _escapeArgs;
    UIntVector  _controlArgs;
    UInt8Vector _operatingSystemCommand;
    uint8_t     _characterSetType;
    wchar_t     _codepoint;
    int         _remainingBytesInChar;
    bool        _invalidSequence;
    bool        _hasQuestionMark;
    bool        _wrapOnControlChar;
    
    enum
    {
        TEXT,
        UNICODE_TEXT,
        ESCAPE_SEQUENCE,
        CHARACTER_SET_SEQUENCE,
        LINE_ATTRIBUTE_SEQUENCE,
        CONTROL_SEQUENCE,
        OPERATING_SYSTEM_COMMAND
    }
    _mode;
};

}

#endif // TERMKIT_PARSER_HPP
