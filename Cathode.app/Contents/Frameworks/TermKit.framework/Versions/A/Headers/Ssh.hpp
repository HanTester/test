//
// Copyright (c) 2014 Secret Geometry, Inc.  All rights reserved.
//

#ifndef TERMKIT_SSH_HPP
#define TERMKIT_SSH_HPP

#include "Types.hpp"
#include <stdint.h>
#include <map>
#include <string>
#include <pthread.h>

namespace term {

struct SshResources;

// 
// Ssh
// 

class Ssh
{
  public:
    
    // 
    Ssh(const char* server,
        const char* user,
        const char* password,
        unsigned int port,
        size_t width,
        size_t height,
        const char* locale,
        const char* termIdentifier,
        StringMap& otherEnvars);
    
    // 
    ~Ssh();
    
    // 
    const char* lookupProcessName();
    
    //
    ConnectionState state() const;
    
    //
    void start();
    
    //
    void update();
    
    //
    const std::string& message() const;
    
    //
    void clearErrorMessage();
    
    //
    void logout();
    
    //
    void suspend();
    
    //
    void resume();
    
    //
    void setPassword(const char* password);
    
    //
    int processCount() const;
    
    //
    void updateProcessInfo();
    
    //
    void resize(size_t width, size_t height);
    
    //
    ssize_t read(uint8_t* str, size_t count);
    
    //
    ssize_t write(const uint8_t* str, size_t count);
    
    //
    void setKeyFile(const char* filename);
    
  private:
    
    bool running() const;
    
    static void* connectThreadMain(void* args);
    static void cleanup(SshResources* resources);
    static void handlePipeError(int sig);
    static std::string getLastSSHError(SshResources* resources);
    
    std::string     _server;
    std::string     _user;
    std::string     _password;
    std::string     _privateKeyFile;
    std::string     _message;
    std::string     _locale;
    std::string     _termIdentifier;
    std::string     _appIdentifier;
    StringMap       _otherEnvars;
    int             _port;
    size_t          _width;
    size_t          _height;
    pthread_t       _thread;
    pthread_mutex_t _mutex;
    ConnectionState _state;
    SshResources*   _resources;
};
    
}

#endif
