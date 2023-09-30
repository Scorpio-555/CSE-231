/***********************************************************************
 * Header File:
 *    Point : The representation of a position on the screen
 * Author:
 *    Br. Helfrich
 * Summary:
 *    Everything we need to know about a location on the screen.
 ************************************************************************/


#pragma once

#include <iostream>

 /*********************************************
  * POINT
  * A single position.
  *********************************************/
class Point
{
public:
    // constructors
    Point() : x(0), y(0) {}
    Point(int location) : x(location % 8), y(location / 8) {};
    Point(int x, int y) : x(x), y(y) {};

    // getters
    int getX()       const { return x; }
    int getY()       const { return y; }
    int getInt()     const { return y * 8 + x; }

    // setters
    void setX(int x) { this->x = x; }
    void setY(int y) { this->y = y; }
    void addX(int dx) { setX(getX() + dx); }
    void addY(int dy) { setY(getY() + dy); }

    bool operator == (const Point& pt) { return pt.getInt() == getInt(); }
    bool operator != (const Point& pt) { return pt.getInt() != getInt(); }

private:
    int x;           // horizontal position
    int y;           // vertical position
};

// stream I/O useful for debugging
std::ostream& operator << (std::ostream& out, const Point& pt);
std::istream& operator >> (std::istream& in, Point& pt);
