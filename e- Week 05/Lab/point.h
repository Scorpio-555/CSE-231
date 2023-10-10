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
    int getInt()     const { if (inBounds()) { return y * 8 + x; } return -1; }

    // setters
    void setX(int x) { this->x = x; }
    void setY(int y) { this->y = y; }
    void addX(int dx) { setX(getX() + dx); }
    void addY(int dy) { setY(getY() + dy); }

    bool inBounds() const { return x >= 0 && x <= 7 && y >= 0 && y <= 7; }
    bool operator == (const Point& pt) { return (pt.x == x && pt.y == y); }
    bool operator != (const Point& pt) { return (pt.x != x || pt.y != y); }
    Point operator + (const Point& pt) { return Point(x + pt.getX(), y + pt.getY()); }

private:
    int x;           // horizontal position
    int y;           // vertical position
};

// stream I/O useful for debugging
std::ostream& operator << (std::ostream& out, const Point& pt);
std::istream& operator >> (std::istream& in, Point& pt);


