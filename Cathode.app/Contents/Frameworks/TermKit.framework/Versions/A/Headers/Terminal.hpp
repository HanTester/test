//
// Copyright (c) 2014 Secret Geometry, Inc.  All rights reserved.
//

#ifndef TERMKIT_TERMINAL_HPP
#define TERMKIT_TERMINAL_HPP

#include "Pty.hpp"
#include "Ssh.hpp"
#include "Parser.hpp"
#include "Dispatcher.hpp"
#include "Context.hpp"
#include "TextArea.hpp"
#include "Utilities.hpp"
#include "Types.hpp"
#include "Config.hpp"
#include "Debug.hpp"
#include <vector>
#include <map>

namespace term {

//
// Terminal
//
// The top level, cross-platform C++ class for TermKit.
// Creates and hooks up a Connection (PTY or SSH), a Parser, a Dispatcher, and a Context.
// Handles input, and holds output.
// Does work in calls to update().
//

template <typename Connection>
class Terminal
{
  public:
    
    // 
    Terminal(const char* server,
             const char* user,
             const char* password,
             unsigned int port,
             size_t width,
             size_t height,
             size_t maxLines,
             BeepCallback beepFunc,
             ResizeCallback resizeFunc,
             const char* locale,
             const char* termIdentifier,
             StringMap& otherEnvars)
    :
        _connection(server, user, password, port, width, height, locale, termIdentifier, otherEnvars),
        _context(width, height, maxLines, beepFunc, resizeFunc),
        _dispatcher(_context),
        _parser(_dispatcher),
        _readBuffer(8 * 1024 * 1024),
        _hasChanges(false)
    {
        #ifdef DO_SANITY_CHECKS
            _context.sanityCheck();
        #endif
    }
    
    ~Terminal()
    {
        // Intentionally empty.  Some Obj-C++ compilers complain if this isn't explicitly defined.
    }
    
    void start()
    {
        _connection.start();
    }
    
    void logout()
    {
        _connection.logout();
    }
    
    void suspend()
    {
        _connection.suspend();
    }
    
    void resume()
    {
        LineLocation lastLineLoc = _context.textArea().lastLineEnd();
        GridLocation lastGridLoc = _context.textArea().gridLocForLineLoc(lastLineLoc);
        
        std::wstring message = L"Resuming...";
        
        _context.setCursorLoc(lastGridLoc);
        _context.pushCursorToFirstColOfNewLine();
        _context.echo(message.data(), message.size());
        _context.pushCursorToFirstColOfNewLine();
        
        _hasChanges = true;
        
        _connection.resume();
    }
    
    Connection& connection()
    {
        return _connection;
    }
    
    Context& context()
    {
        return _context;
    }
    
    const Context& context() const
    {
        return _context;
    }
    
    TextArea& textArea()
    {
        return _context.textArea();
    }
    
    const TextArea& textArea() const
    {
        return _context.textArea();
    }
    
    void setPassword(const char* password)
    {
        _connection.setPassword(password);
    }
    
    size_t columnCount() const
    {
        return _context.textArea().width();
    }
    
    size_t rowCount() const
    {
        return _context.textArea().height();
    }
    
    void setColumnCount(size_t cols)
    {
        resize(cols, rowCount());
    }
    
    void setRowCount(size_t rows)
    {
        resize(columnCount(), rows);
    }
    
    void resize(size_t cols, size_t rows)
    {
        #ifdef DO_SANITY_CHECKS
            _context.sanityCheck();
        #endif
        
        update();
        
        #ifdef DO_SANITY_CHECKS
            _context.sanityCheck();
        #endif
        
        _context.resize(cols, rows);
        _connection.resize(cols, rows);
        _hasChanges = true;
        
        #ifdef DO_SANITY_CHECKS
            _context.sanityCheck();
        #endif
        
        update();
        
        #ifdef DO_SANITY_CHECKS
            _context.sanityCheck();
        #endif
    }
    
    GridLocation cursorLoc() const
    {
        return _context.cursorLoc();
    }
    
    const std::string& activeProcessName() const
    {
        return _connection.activeProcessName();
    }
    
    const std::vector<std::string>& allProcessNames() const
    {
        return _connection.allProcessNames();
    }
    
    bool hasChanges() const
    {
        return _hasChanges;
    }
    
    void setHasChanges(bool b)
    {
        _hasChanges = b;
    }
    
    ConnectionState state() const
    {
        return _connection.state();
    }
    
    const std::string& message() const
    {
        return _connection.message();
    }
    
    void clearErrorMessage()
    {
        _connection.clearErrorMessage();
    }
    
    void clearBuffer()
    {
        _context.clearBuffer();
        _hasChanges = true;
    }
    
    void write(uint8_t c)
    {
        write(&c, 1);
    }
    
    void write(const char* s)
    {
        if (s == nullptr)
            return;
        
        size_t length = strlen(s);
        
        write((const uint8_t*)s, length);
    }
    
    void write(const uint8_t* str, size_t count)
    {
        size_t bytesWritten = 0;
        size_t bytesRemaining = count;
        
        while (true)
        {
            ssize_t writeCount = _connection.write(str, bytesRemaining);
            
            if (writeCount < 0)
            {
                if (errno != EAGAIN)
                    break;
            }
            else
            {
                str += writeCount;
                bytesWritten += writeCount;
                bytesRemaining -= writeCount;
            }
            
            if (bytesWritten < count)
                update();
            else
                break;
        }
    }
    
    void update()
    {
        update(_readBuffer.size());
    }
    
    void update(size_t numBytes)
    {
        // Handy for debugging.
        //numBytes = 1;
        
        _connection.update();
        
        if (_connection.state() == ConnectionState_Disconnected ||
            _connection.state() == ConnectionState_Suspended)
            return;
        
        if (numBytes == 0)
            return;
        
        if (numBytes > _readBuffer.size())
            numBytes = _readBuffer.size();
        
        // Grab any new data from the connection and put it into the buffer.
        ssize_t count = _connection.read(_readBuffer.data(), numBytes);
        
        if (count <= 0)
            return;
        
        #ifdef DO_SANITY_CHECKS
            _context.sanityCheck();
        #endif
        
        // Pass the buffer of new data to the parser.  This starts a complex chain of actions.
        // The parser breaks the data into text and various types of command sequences; it sends these to the dispatcher.
        // The dispatcher translates everything it receives into calls to member functions of the context.
        // The context's methods modify the text, cursor, style, scroll, etc.
        _parser.parse(_readBuffer.data(), count);
        
        // If the context has prepared a response, write it back to the connection.
        write(_context.getResponse());
        
        _hasChanges = true;
        
        _connection.updateProcessInfo();
        
        #ifdef DO_SANITY_CHECKS
            _context.sanityCheck();
        #endif
        
        return;
    }
    
    void upArrowKey()       { write(ESC_STRING "OA"); }
    void downArrowKey()     { write(ESC_STRING "OB"); }
    void rightArrowKey()    { write(ESC_STRING "OC"); }
    void leftArrowKey()     { write(ESC_STRING "OD"); }
    void moveWordLeft()     { write(ESC_STRING "b"); }
    void moveWordRight()    { write(ESC_STRING "f"); }
    void forwardDeleteKey() { write(CSI_PREFIX_STRING "3~"); }
    void pageUpKey()        { write(CSI_PREFIX_STRING "5~"); }
    void pageDownKey()      { write(CSI_PREFIX_STRING "6~"); }
    
    void functionKey(int index)
    {
        switch (index)
        {
            case 1:  write(ESC_STRING "OP"); break;
            case 2:  write(ESC_STRING "OQ"); break;
            case 3:  write(ESC_STRING "OR"); break;
            case 4:  write(ESC_STRING "OS"); break;
                
            case 5:  write(CSI_PREFIX_STRING "15~"); break;
            case 6:  write(CSI_PREFIX_STRING "17~"); break;
            case 7:  write(CSI_PREFIX_STRING "18~"); break;
            case 8:  write(CSI_PREFIX_STRING "19~"); break;
            case 9:  write(CSI_PREFIX_STRING "20~"); break;
            case 10: write(CSI_PREFIX_STRING "21~"); break;
            case 11: write(CSI_PREFIX_STRING "23~"); break;
            case 12: write(CSI_PREFIX_STRING "24~"); break;
            case 13: write(CSI_PREFIX_STRING "25~"); break;
            case 14: write(CSI_PREFIX_STRING "26~"); break;
            case 15: write(CSI_PREFIX_STRING "28~"); break;
            case 16: write(CSI_PREFIX_STRING "29~"); break;
            case 17: write(CSI_PREFIX_STRING "31~"); break;
            case 18: write(CSI_PREFIX_STRING "32~"); break;
            case 19: write(CSI_PREFIX_STRING "33~"); break;
            case 20: write(CSI_PREFIX_STRING "34~"); break;
        }
    }
    
  private:
    
    Connection  _connection;
    Context     _context;
    Dispatcher  _dispatcher;
    Parser      _parser;
    UInt8Vector _readBuffer;
    bool        _hasChanges;
};

typedef Terminal<Ssh> SshTerminal;
typedef Terminal<Pty> PtyTerminal;

}

#endif
