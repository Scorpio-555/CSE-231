#pragma once

#include <list>
#include "earth.h"
#include "mobile.h"
#include "satellite.h"
#include "star.h"
#include "uiInteract.h"

#define PI 3.14159265359

class TestGame;

class Game {
	friend class TestGame;
public:
	Game() {}
	Game(double timeInterval, double earthRadius, double earthRotationSpeed, bool spawnStars);
	static double getTimeInterval();
	static double getEarthRadius();
	static Position getEarthPosition();
	static double getEarthRotationSpeed();

	static void advance(const Interface* pUI);
	static void checkCollisions();
	static void removeZombies();
	static void addMobile(Mobile* mobile);
	static void addDebris(Mobile* mobile);
	static void killShip();
	static void draw();

private:
	static void reset();

	static double timeInterval;
	static Earth earth;
	static Ship* ship;
	static list<Mobile*> mobileList;
	static list<Mobile*> onDeck;
	static list<Star> stars;
};
