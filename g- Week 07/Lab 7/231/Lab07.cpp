/*************************************************************
 * 1. Name:
 *      Demo
 * 2. Assignment Name:
 *      Lab 07: Orbit Simulator
 * 3. Assignment Description:
 *      Simulate satellites orbiting the earth
 * 4. What was the hardest part? Be as specific as possible.
 *      The hardest part was realizing that ddx in the white board demo
 *      uses sine instead of cosine, and ddy uses cosine instead of sine.
 *      Still very confused as to why that is, but it means the difference
 *      between shooting away from earth tangental to its surface and orbiting
 *      the earth.
 * 5. How long did it take for you to complete the assignment?
 *      1 hr 30 min
 *****************************************************************/

#include <cassert>      // for ASSERT
#include "uiInteract.h" // for INTERFACE
#include "uiDraw.h"     // for RANDOM and DRAW*
#include "position.h"      // for POINT
#include "trig.h"
#include "math.h"


#define PI 3.14159265359
#define rotation_speed (2 * PI) / 1800
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
        ptSputnik.setMetersX(0.0);
        ptSputnik.setMetersY(42164000.0);

        sputnikDx = -geo_speed;
        sputnikDy = 0;

        ptStar.setPixelsX(ptUpperRight.getPixelsX() * random(-0.5, 0.5));
        ptStar.setPixelsY(ptUpperRight.getPixelsY() * random(-0.5, 0.5));

        angleShip = 3 * PI / 2;
        angleEarth = 0.0;
        phaseStar = 0;
    }

    double getHeight(Position pt) {
        return Trig::distanceBetweenPoints(Position(0, 0), pt) - earth_radius;
    }

    double get_gH(double height) {
        return g * pow(earth_radius / (earth_radius + height), 2);
    }

    double getDdx(Position pt) {
        return Trig::computeSineComponent(Trig::getAngle(pt.getMetersX(), pt.getMetersY()), get_gH(getHeight(pt)));
    }

    double getDdy(Position pt) {
        return Trig::computeCosineComponent(Trig::getAngle(ptSputnik.getMetersX(), ptSputnik.getMetersY()), get_gH(getHeight(pt)));
    }

    Position ptSputnik;
    Position ptShip;
    Position ptStar;
    Position ptUpperRight;

    unsigned char phaseStar;

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
    pDemo->angleEarth -= rotation_speed;

    double ddx = pDemo->getDdx(pDemo->ptSputnik);
    double ddy = pDemo->getDdy(pDemo->ptSputnik);

    pDemo->sputnikDx += ddx * t;
    pDemo->sputnikDy += ddy * t;
    pDemo->ptSputnik.addMetersX(pDemo->sputnikDx * t);
    pDemo->ptSputnik.addMetersY(pDemo->sputnikDy * t);
    pDemo->angleShip -= rotation_speed;
    pDemo->phaseStar++;

    //
    // draw everything
    //

    Position pt;
    ogstream gout(pt);

    gout.drawSputnik(pDemo->ptSputnik, pDemo->angleShip);

    // draw a single star
    gout.drawStar(pDemo->ptStar, pDemo->phaseStar);

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
