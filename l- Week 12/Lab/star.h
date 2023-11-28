/***********************************************************************
 * Header File:
 *    STAR : just a little star for the background
 *
 * Author:
 *    Jaden Myers
 * Summary:
 *    star for background image of the screen
 ************************************************************************/

#pragma once

#include "position.h"

class Star
{
public:
    Star();
    Star(Position pt);
    void phaseShift() { phase++; }
    void draw();
    Position getPoint() { return pt; }
    unsigned char getPhase() { return phase; }

private:
    Position pt;
    unsigned char phase;
};
