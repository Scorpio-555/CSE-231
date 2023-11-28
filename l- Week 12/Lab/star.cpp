/***********************************************************************
 * Header File:
 *    STAR : just a little star for the background
 *
 * Author:
 *    Jaden Myers
 * Summary:
 *    star for background image of the screen
 ************************************************************************/

#include "star.h"
#include "position.h"
#include "uiDraw.h"

 /******************************************
   * POINT : CONSTRUCTOR WITH X,Y
   * Initialize the point to the passed position
   *****************************************/
Star::Star(Position pt)
{
    this->pt = pt;
    phase = random(0, 255);
}

void Star::draw()
{
    Position position;
    ogstream gout(position);
    gout.drawStar(pt, phase);
}

/******************************************
   * POINT : CONSTRUCTOR WITH X,Y
   * Initialize the point to the passed position
   *****************************************/
Star::Star()
{
    pt = Position();
    phase = random(0, 255);
}
