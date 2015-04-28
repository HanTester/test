#ifndef TERMKIT_DEBUG_HPP
#define TERMKIT_DEBUG_HPP

#ifdef DEBUG

    #ifdef __APPLE__
    
        #include "TargetConditionals.h"

        #if TARGET_OS_IPHONE

            #include <signal.h>
            #define TERMKIT_ASSERT(b) { if (!(b)) raise(SIGINT); }

        #elif TARGET_IPHONE_SIMULATOR

            #include <signal.h>
            #define TERMKIT_ASSERT(b) { if (!(b)) raise(SIGINT); }

        #elif TARGET_OS_MAC

            #include <MacTypes.h>
            #define TERMKIT_ASSERT(b) { if (!(b)) Debugger(); }

        #endif

    #elif __linux

        #define TERMKIT_ASSERT(b) { if (!(b)) kill(getpid(), SIGINT); }

    #endif

#else // RELEASE

    // In release mode, asserts do absolutely nothing.
    #define TERMKIT_ASSERT(b) // nothing

#endif

// For code that should never be reached.
#define TERMKIT_NEVER TERMKIT_ASSERT(false)

#endif
