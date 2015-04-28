//
// Copyright (c) 2014 Secret Geometry, Inc.  All rights reserved.
//

#ifndef TERMKIT_PTY_HPP
#define TERMKIT_PTY_HPP

#include "Types.hpp"
#include <string>
#include <map>
#include <stdint.h>
#include <sys/sysctl.h>

namespace term {

// 
// Pty
//
// A pty represents a device that can send and receive data.
// A device has a current process, a number of child processes, and a preferred grid size.
// In modern computing a Pty is merely an operating system abstraction that resembles a separate machine.
// 

class Pty
{
  public:

    // 
    Pty(const char* server,
        const char* user,
        const char* password,
        unsigned int port,
        size_t width,
        size_t height,
        const char* locale,
        const char* termIdentifier,
        StringMap& otherEnvars);
    
    // 
    ~Pty();
    
    //
    void start();
    
    //
    void update();
    
    //
    ssize_t read(uint8_t* str, size_t count);
    
    //
    ssize_t write(const uint8_t* str, size_t count);
    
    //
    void logout();
    
    //
    void suspend();
    
    //
    void resume();
    
    //
    void setPassword(const char* password);
    
    //
    void resize(size_t width, size_t height);
    
    //
    ConnectionState state() const;
    
    //
    const std::string& message() const;
    
    //
    void clearErrorMessage();
    
    //
    const std::string& activeProcessName() const;
    
    //
    const std::string& workingPath() const;
    
    //
    const std::vector<std::string>& allProcessNames() const;
    
    //
    void updateProcessInfo();
    
  private:
    
    bool running() const;
    
    static void childProcessEnded(int sig);

    pid_t _pid;
    int _file;
    std::string _message;
    std::string _processName;
    std::string _workingPath;
    std::vector<std::string> _processNames;
    ConnectionState _state;
};

}

#endif
