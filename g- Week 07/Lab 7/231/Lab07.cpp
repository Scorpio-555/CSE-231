/*************************************************************
 * 1. Name:
 *      Demo
 * 2. Assignment Name:
 *      Lab 07: Orbit Simulator
 * 3. Assignment Description:
 *      Simulate satellites orbiting the earth
 * 4. What was the hardest part? Be as specific as possible.
 *      ??
 * 5. How long did it take for you to complete the assignment?
 *      ??
 *****************************************************************/

#include <cassert>      // for ASSERT
#include "uiInteract.h" // for INTERFACE
#include "uiDraw.h"     // for RANDOM and DRAW*
#include "position.h"      // for POINT
#include "trig.h"
#include "math.h"


#define PI 3.14159265359
#define t 48
#define earth_radius 6378000
#define geo_distance 42164000
#define g -9.8067
#define geo_speed 3100



using namespace std;

/*************************************************************************
 * Demo
 * Test structure to capture the LM that will move around the screen
 *************************************************************************/
class Demo
{
public:
   Demo(Position ptUpperRight) :
      ptUpperRight(ptUpperRight)
   {
//      ptHubble.setPixelsX(ptUpperRight.getPixelsX() * random(-0.5, 0.5));
//      ptHubble.setPixelsY(ptUpperRight.getPixelsY() * random(-0.5, 0.5));

       ptSputnik.setMetersX(-1.0);
       ptSputnik.setMetersY(42164000.0);
       
       sputnikDx = -geo_speed;
       sputnikDy = 0;
       
       sputnikHeight = Trig::distanceBetweenPoints(Position(0,0), ptSputnik) - earth_radius;
       
        gh = g * pow(earth_radius / (earth_radius + sputnikHeight),2);
       
       double newAngle = Trig::getAngle(ptSputnik.getMetersX(), ptSputnik.getMetersY());
       
       
       sputnikDDx = Trig::computeSineComponent(Trig::getAngle(ptSputnik.getMetersX(), ptSputnik.getMetersY()), gh);
       
       sputnikDDy = Trig::computeCosineComponent(Trig::getAngle(ptSputnik.getMetersX(), ptSputnik.getMetersY()), gh);
        
        
//      ptStarlink.setPixelsX(ptUpperRight.getPixelsX() * random(-0.5, 0.5));
//      ptStarlink.setPixelsY(ptUpperRight.getPixelsY() * random(-0.5, 0.5));
//
//      ptCrewDragon.setPixelsX(ptUpperRight.getPixelsX() * random(-0.5, 0.5));
//      ptCrewDragon.setPixelsY(ptUpperRight.getPixelsY() * random(-0.5, 0.5));
//
//      ptShip.setPixelsX(ptUpperRight.getPixelsX() * random(-0.5, 0.5));
//      ptShip.setPixelsY(ptUpperRight.getPixelsY() * random(-0.5, 0.5));
//
//      ptGPS.setPixelsX(ptUpperRight.getPixelsX() * random(-0.5, 0.5));
//      ptGPS.setPixelsY(ptUpperRight.getPixelsY() * random(-0.5, 0.5));
//
//      ptStar.setPixelsX(ptUpperRight.getPixelsX() * random(-0.5, 0.5));
//      ptStar.setPixelsY(ptUpperRight.getPixelsY() * random(-0.5, 0.5));

      angleShip = 0.0;
      angleEarth = 0.0;
      phaseStar = 0;
   }

   Position ptHubble;
   Position ptSputnik;
   Position ptStarlink;
   Position ptCrewDragon;
   Position ptShip;
   Position ptGPS;
   Position ptStar;
   Position ptUpperRight;

    unsigned char phaseStar;

    
    double gh;
    double sputnikHeight;
    
    double angleShip;
    double angleEarth;
    
   double sputnikDx;
   double sputnikDy;
    double sputnikDDx;
    double sputnikDDy;
};

/*************************************
 * All the interesting work happens here, when
 * I get called back from OpenGL to draw a frame.
 * When I am finished drawing, then the graphics
 * engine will wait until the proper amount of
 * time has passed and put the drawing on the screen.
 **************************************/
void callBack(const Interface* pUI, void* p)
{
   // the first step is to cast the void pointer into a game object. This
   // is the first step of every single callback function in OpenGL. 
   Demo* pDemo = (Demo*)p;

   //
   // accept input
   //

   // move by a little
   if (pUI->isUp())
      pDemo->ptShip.addPixelsY(1.0);
   if (pUI->isDown())
      pDemo->ptShip.addPixelsY(-1.0);
   if (pUI->isLeft())
      pDemo->ptShip.addPixelsX(-1.0);
   if (pUI->isRight())
      pDemo->ptShip.addPixelsX(1.0);


   //
   // perform all the game logic
   //

   // rotate the earth
    pDemo->angleEarth -= (2 * PI ) / 1800;
    
    pDemo->sputnikDDx = Trig::computeSineComponent(Trig::getAngle(pDemo->ptSputnik.getMetersX(), pDemo->ptSputnik.getMetersY()), pDemo->gh);
    
    pDemo->sputnikDDy = Trig::computeCosineComponent(Trig::getAngle(pDemo->ptSputnik.getMetersX(), pDemo->ptSputnik.getMetersY()), pDemo->gh);
    
    pDemo->sputnikDx += pDemo->sputnikDDx * t;
    pDemo->sputnikDy += pDemo->sputnikDDy * t;
    pDemo->ptSputnik.addMetersX(pDemo->sputnikDDx * t);
    pDemo->ptSputnik.addMetersY(pDemo->sputnikDDy * t);
   pDemo->angleShip += 0.02;
   //pDemo->phaseStar++;

   //
   // draw everything
   //

   Position pt;
   ogstream gout(pt);

   // draw satellites
//   gout.drawCrewDragon(pDemo->ptCrewDragon, pDemo->angleShip);
//   gout.drawHubble    (pDemo->ptHubble,     pDemo->angleShip);
   gout.drawSputnik   (pDemo->ptSputnik,    pDemo->angleShip);
//   gout.drawStarlink  (pDemo->ptStarlink,   pDemo->angleShip);
//   gout.drawShip      (pDemo->ptShip,       pDemo->angleShip, pUI->isSpace());
//   gout.drawGPS       (pDemo->ptGPS,        pDemo->angleShip);

//   // draw parts
//   pt.setPixelsX(pDemo->ptCrewDragon.getPixelsX() + 20);
//   pt.setPixelsY(pDemo->ptCrewDragon.getPixelsY() + 20);
//   gout.drawCrewDragonRight(pt, pDemo->angleShip); // notice only two parameters are set
//   pt.setPixelsX(pDemo->ptHubble.getPixelsX() + 20);
//   pt.setPixelsY(pDemo->ptHubble.getPixelsY() + 20);
//   gout.drawHubbleLeft(pt, pDemo->angleShip);      // notice only two parameters are set
//   pt.setPixelsX(pDemo->ptGPS.getPixelsX() + 20);
//   pt.setPixelsY(pDemo->ptGPS.getPixelsY() + 20);
//   gout.drawGPSCenter(pt, pDemo->angleShip);       // notice only two parameters are set
//   pt.setPixelsX(pDemo->ptStarlink.getPixelsX() + 20);
//   pt.setPixelsY(pDemo->ptStarlink.getPixelsY() + 20);
//   gout.drawStarlinkArray(pt, pDemo->angleShip);   // notice only two parameters are set

//   // draw fragments
//   pt.setPixelsX(pDemo->ptSputnik.getPixelsX() + 20);
//   pt.setPixelsY(pDemo->ptSputnik.getPixelsY() + 20);
//   gout.drawFragment(pt, pDemo->angleShip);
//   pt.setPixelsX(pDemo->ptShip.getPixelsX() + 20);
//   pt.setPixelsY(pDemo->ptShip.getPixelsY() + 20);
//   gout.drawFragment(pt, pDemo->angleShip);

//   // draw a single star
//   gout.drawStar(pDemo->ptStar, pDemo->phaseStar);

   // draw the earth
   pt.setMeters(0.0, 0.0);
   gout.drawEarth(pt, pDemo->angleEarth);
}

double Position::metersFromPixels = 40.0;

/*********************************
 * Initialize the simulation and set it in motion
 *********************************/
#ifdef _WIN32_X
#include <windows.h>
int WINAPI wWinMain(
   _In_ HINSTANCE hInstance,
   _In_opt_ HINSTANCE hPrevInstance,
   _In_ PWSTR pCmdLine,
   _In_ int nCmdShow)
#else // !_WIN32
int main(int argc, char** argv)
#endif // !_WIN32
{
   // Initialize OpenGL
   Position ptUpperRight;
   ptUpperRight.setZoom(128000.0 /* 128km equals 1 pixel */);
   ptUpperRight.setPixelsX(1000.0);
   ptUpperRight.setPixelsY(1000.0);
   Interface ui(0, NULL,
      "Demo",   /* name on the window */
      ptUpperRight);

   // Initialize the demo
   Demo demo(ptUpperRight);

   // set everything into action
   ui.run(callBack, &demo);


   return 0;
}
