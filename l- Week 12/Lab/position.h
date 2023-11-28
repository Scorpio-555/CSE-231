/***********************************************************************
 * Header File:
 *    Point : The representation of a position 
 * Author:
 *    Br. Helfrich
 * Summary:
 *    Everything we need to know about a location on the screen
 *    or the location on the field.
 ************************************************************************/


#pragma once

#include <iostream> 
#include <cmath>
#include "trig.h"
#include "angle.h"

class TestPosition;
class Acceleration;
class Velocity;

/*********************************************
 * Position
 * A single position on the field in Meters  
 *********************************************/
class Position
{
public:
   friend TestPosition;
   
   // constructors
   Position()            : x(0.0), y(0.0)  {}
   Position(double x, double y);
   Position(const Position & pt) : x(pt.x), y(pt.y) {}
   Position& operator = (const Position& pt);
   bool operator == (const Position& pt);

   // getters
   double getMetersX()       const { return x;                    }
   double getMetersY()       const { return y;                    }
   double getPixelsX()       const { return x / metersFromPixels; }
   double getPixelsY()       const { return y / metersFromPixels; }
   bool isOutOfBounds() { return getPixelsX() < -500.0 || getPixelsX() > 500.0 || getPixelsY() < -500.0 || getPixelsY() > 500.0; }

   // setters
   void setMeters(double xMeters, double yMeters) {x = xMeters; y = yMeters; }
   void setMetersX(double xMeters)       { x = xMeters;           }
   void setMetersY(double yMeters)       { y = yMeters;           }
   void setPixelsX(double xPixels)       { x = xPixels * metersFromPixels;          }
   void setPixelsY(double yPixels)       { y = yPixels * metersFromPixels;          }
   void addMetersX(double dxMeters)      { setMetersX(getMetersX() + dxMeters);     }
   void addMetersY(double dyMeters)      { setMetersY(getMetersY() + dyMeters);     }
   void addPixelsX(double dxPixels)      { setPixelsX(getPixelsX() + dxPixels);     }
   void addPixelsY(double dyPixels)      { setPixelsY(getPixelsY() + dyPixels);     }

   // deal with the ratio of meters to pixels
   void setZoom(double metersFromPixels)
   {
      this->metersFromPixels = metersFromPixels;
   }
   
   double getZoom() const { return metersFromPixels; }

private:
   double x;                 // horizontal position
   double y;                 // vertical position
   static double metersFromPixels;
};

/*********************************************
 * COMPUTE DISTANCE
 * Find the distance between two positions
 *********************************************/
inline double computeDistance(const Position& pos1, const Position& pos2)
{
   return sqrt((pos1.getMetersX() - pos2.getMetersX()) * (pos1.getMetersX() - pos2.getMetersX()) +
               (pos1.getMetersY() - pos2.getMetersY()) * (pos1.getMetersY() - pos2.getMetersY()));
}

// stream I/O useful for debugging
std::ostream & operator << (std::ostream & out, const Position& pt);
std::istream & operator >> (std::istream & in,        Position& pt);


/*********************************************
 * PT
 * Trivial point
 *********************************************/
struct PT
{
   double x;
   double y;
};

class Velocity {
public:
    Velocity() : dx(0.0), dy(0.0) {}
    Velocity(double dx, double dy) : dx(dx), dy(dy) {}
    Velocity(Angle& a, double total) {
        dx = Trig::computeSineComponent(a.getRadians(), total);
        dy = Trig::computeCosineComponent(a.getRadians(), total);
    }
    double getDx() const { return dx; }
    double getDy() const { return dy; }
    double getTotal() const { return Trig::computeTotalComponent(dx, dy); }
    void addDx(double dx) { this->dx += dx; }
    void addDy(double dy) { this->dy += dy; }
    void add(Velocity v) { 
        addDx(v.getDx()); 
        addDy(v.getDy()); 
    }
private:
    double dx;
    double dy;
};

