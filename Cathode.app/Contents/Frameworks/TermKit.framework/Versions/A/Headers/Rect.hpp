//
//  Rect.hpp
//  TermKit
//
//  Created by Colin Caufield on 1/19/2014.
// Copyright (c) 2014 Secret Geometry, Inc.  All rights reserved.
//

#ifndef TERMKIT_RECT
#define TERMKIT_RECT

#include "Types.hpp"
#include "Debug.hpp"

namespace term
{

struct Rect
{
    GridLocation location;
    GridSize size;
    
    Rect(const GridLocation& l, const GridSize& s) : location(l), size(s) {}
    
    Rect(int x, int y, int sx, int sy) : location(x, y), size(sx, sy) {}
    
    bool operator==(const Rect& other) const
    {
        return location == other.location && size == other.size;
    }
    
    bool operator!=(const Rect& other) const
    {
        return !(*this == other);
    }
    
    bool contains(const Rect& other) const
    {
        bool inx = (location.x <= other.location.x) && (other.location.x + other.size.x <= location.x + size.x);
        bool iny = (location.y <= other.location.y) && (other.location.y + other.size.y <= location.y + size.y);
        
        return inx && iny;
    }
    
    bool touches(const Rect& other) const
    {
        return touchesInX(other) || touchesInY(other);
    }
    
    bool touchesInX(const Rect& other) const
    {
        int thisLeft = location.x;
        int thisRight = location.x + size.x;
        int otherLeft = other.location.x;
        int otherRight = other.location.x + other.size.x;
        
        bool isLeft = otherRight < thisLeft;
        bool isRight = otherLeft > thisRight;
        
        bool outside = isLeft || isRight;
        return !outside;
    }
    
    bool touchesInY(const Rect& other) const
    {
        int thisBottom = location.y;
        int thisTop = location.y + size.y;
        int otherBottom = other.location.y;
        int otherTop = other.location.y + other.size.y;
        
        bool isBelow = otherTop < thisBottom;
        bool isAbove = otherBottom > thisTop;
        
        bool outside = isBelow || isAbove;
        return !outside;
    }
    
    void join(const Rect& other)
    {
        TERMKIT_ASSERT(touches(other));
        
        bool sameX = location.x == other.location.x;
        bool sameY = location.y == other.location.y;
        bool sameWidth = size.x == other.size.x;
        bool sameHeight = size.y == other.size.y;
        
        if (sameY && sameHeight)
        {
            int end = std::max(location.x + size.x, other.location.x + other.size.x);
            location.x = std::min(location.x, other.location.x);
            size.x = end - location.x;
        }
        else if (sameX && sameWidth)
        {
            int end = std::max(location.y + size.y, other.location.x + other.size.y);
            location.y = std::min(location.y, other.location.y);
            size.y = end - location.y;
        }
        else TERMKIT_ASSERT(false);
    }
    
    void enclose(const Rect& other)
    {
        int endx = std::max(location.x + size.x, other.location.x + other.size.x);
        int endy = std::max(location.y + size.y, other.location.y + other.size.y);
        
        location.x = std::min(location.x, other.location.x);
        location.y = std::min(location.y, other.location.y);
        
        size.x = endx - location.x;
        size.y = endy - location.y;
    }
    
    friend std::ostream& operator<<(std::ostream& stream, const Rect& rect)
    {
        stream << "[ location:" << rect.location << ", size:" << rect.size << "]";
        return stream;
    }
};

typedef std::vector<Rect> RectVector;

}

#endif
