#include "game.h"

double Game::timeInterval = 0.0;
Earth Game::earth = Earth();
Ship* Game::ship = nullptr;
list<Mobile> Game::mobileList = list<Mobile>();

double Game::getTimeInterval()
{
	return timeInterval;
}

double Game::getEarthRadius()
{
	return earth.getRadius();
}

Position Game::getEarthPosition()
{
	return earth.getPosition();
}

double Game::getEarthRotationSpeed()
{
	return earth.getRotationSpeed();
}

void Game::advance()
{
}

void Game::checkCollisions()
{
}

void Game::removeZombies()
{
}

void Game::addMobile(Mobile mobile)
{
}

void Game::killShip()
{
}
