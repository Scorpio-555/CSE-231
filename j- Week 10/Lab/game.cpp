#include "game.h"
#include "trig.h"

double Game::timeInterval = 0.0;
Earth Game::earth = Earth();
Ship* Game::ship = nullptr;
list<Mobile*> Game::mobileList = list<Mobile*>();

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
	for (Mobile* m : mobileList) {
		m->move();
	}
}

void Game::checkCollisions()
{
	for (auto it = mobileList.begin(); it != mobileList.end(); ++it) {
		Mobile* mobile1 = *it;
		if (mobile1->getHeight() <= mobile1->getRadius()) {
			mobile1->kill();
		}

		auto it2 = it;
		++it2;

		for (it2; it2 != mobileList.end(); ++it2) {
			Mobile* mobile2 = *it2;
			double distance = Trig::distanceBetweenPoints(mobile1->getPosition(), mobile2->getPosition());
			double threshold = mobile1->getRadius() + mobile2->getRadius();
			if (distance <= threshold) {
				mobile1->kill();
				mobile2->kill();
			}
		}
	}
}

void Game::removeZombies()
{
	for (auto it = mobileList.begin(); it != mobileList.end();)
		if ((*it)->isAlive() == false)
		{
			it = mobileList.erase(it);
		}
		else
			++it;
}

void Game::addMobile(Mobile* mobile)
{
	mobileList.push_back(mobile);
}

void Game::killShip()
{
	ship = nullptr;
}
