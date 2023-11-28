#pragma once

#define TWO_PI 6.28318530718

#include <math.h>    // for floor()
#include <iostream>  // for cout
#include <cassert>   // for assert()
using namespace std;

/************************************
 * ANGLE
 ************************************/
class Angle
{

public:
    // Default constructor
    Angle() : radians(0.0) {}
    Angle(const Angle& rhs) : radians(rhs.radians) {}
    Angle(double degrees) : radians(0.0)
    {
        setDegrees(degrees);
    }

    // Getters
    double getDegrees() const;
    double getRadians() const;

    // Setters
    void setDegrees(double degrees);
    void setRadians(double radians);
    void addRadians(double radians);
    void addDegrees(double degrees);
    Angle& operator = (const Angle& rhs);
    bool operator == (const Angle& rhs) const;
    bool operator != (const Angle& rhs) const;
    Angle operator- ();
    ostream& operator<< (ostream& out);
    // Display
    void display(ostream& out) const;

private:
    // Convert functions
    double convertToDegrees(double radians) const;
    double convertToRadians(double degrees) const;

    // Normalize
    double normalize(double radians) const;

    double radians;
};
