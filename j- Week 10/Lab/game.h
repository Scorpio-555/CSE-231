#pragma once

#include <list>
#include "earth.h"
#include "mobile.h"

class TestGame;

class Game {
	friend class TestGame;
public:
	Game() {}
	Game(double timeInterval, double earthRadius, double earthRotationSpeed) {
		this->timeInterval = timeInterval;
		this->earth = Earth(earthRadius, earthRotationSpeed);
	}
	static double getTimeInterval();
	static double getEarthRadius();
	static Position getEarthPosition();
	static double getEarthRotationSpeed();

	static void advance();
	static void checkCollisions();
	static void removeZombies();
	static void addMobile(Mobile mobile);
	static void killShip();

private:
	static double timeInterval;
	static Earth earth;
	static Ship* ship;
	static list<Mobile> mobileList;
};
