#include "mobile.h"
#include "trig.h"
#include "game.h"

#define GRAVITY -9.8067

Position Mobile::getPosition()
{
	return position;
}

double Mobile::getRadius()
{
	return radius;
}

double Mobile::getHeight()
{
	return Trig::distanceBetweenPoints(Game::getEarthPosition(), position) - Game::getEarthRadius();
}

double Mobile::get_gH()
{
	return GRAVITY * pow(Game::getEarthRadius() / (Game::getEarthRadius() + getHeight()), 2);
}

double Mobile::getGravityDdx()
{
	return Trig::computeSineComponent(Trig::getAngle(position.getMetersX(), position.getMetersY()), get_gH());
}

double Mobile::getGravityDdy()
{
	return Trig::computeCosineComponent(Trig::getAngle(position.getMetersX(), position.getMetersY()), get_gH());
}

bool Mobile::isAlive()
{
	return alive;
}

void Mobile::kill()
{
	alive = false;
}

void Mobile::move()
{
	double t = Game::getTimeInterval();
	double ddx = getGravityDdx();
	double ddy = getGravityDdy();

	dx += ddx * t;
	dy += ddy * t;
	position.addMetersX(dx * t);
	position.addMetersY(dy * t);
	rotationAngle.addRadians(rotationSpeed);
}

void Ship::kill() {
	alive = false;
	Game::killShip();
}
