//
// Copyright (c) 2014 Secret Geometry, Inc.  All rights reserved.
//

#ifndef TERMKIT_HELPERS_HPP
#define TERMKIT_HELPERS_HPP

#include "Types.hpp"
#include <algorithm>

namespace term {

//
// Adds the given combiner to the given character as a "combining diacritic."
// For example, 'e' and '´' make é.
//
wchar_t combineCodepoints(wchar_t character, wchar_t combiner);

//
// Simple clamp function.
//
template <typename T>
T clamp(const T& value, const T& min, const T& max)
{
    return std::max(min, std::min(max, value));
}

}

#endif
