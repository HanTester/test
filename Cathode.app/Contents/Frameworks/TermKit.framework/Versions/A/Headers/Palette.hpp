//
// Copyright (c) 2014 Secret Geometry, Inc.  All rights reserved.
//

#ifndef TERMKIT_PALETTE_HPP
#define TERMKIT_PALETTE_HPP

#include "Types.hpp"

namespace term {

    
// 

void getRGBForIndex(uint8_t index, float rgb[3]);

uint8_t getIndexForRGB(float rgb[3]);

// 

uint8_t grayscaleIndexForRGB(float rgb[3]);

uint8_t rgb16IndexForRGB(float rgb[3]);

uint8_t rgb256IndexForRGB(float rgb[3]);

}

#endif
