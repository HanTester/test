//
//  GLUtilities.h
//  GLKit
//
//  Created by Colin Caufield on 11-06-24.
//  Copyright 2011 Secret Geometry. All rights reserved.
//

#ifdef GL_DEBUG
    #define GL_ASSERT(x)        {if (!(x)) Debugger();}
    #define GL_CHECK_FOR_ERRORS [GLContext checkForErrors]
    #define GL_BEGIN            (void)0
    #define GL_END              (void)0 // GL_CHECK_FOR_ERRORS
#else
    #define GL_ASSERT(x)        (void)0
    #define GL_BEGIN            (void)0
    #define GL_END              (void)0
    #define GL_CHECK_FOR_ERRORS (void)0
#endif
