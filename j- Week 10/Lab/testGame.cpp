#include "testGame.h"
#include "game.h"
#include <iostream>

#define PI 3.14159265359
#define ROTATION_SPEED (2 * PI) / 1800
#define TIME_INTERVAL 48
#define	RADIUS 6378000

using namespace std;

void TestGame::run()
{
	testGetTimeInterval();
	testGetEarthRadius();
	testGetEarthPosition();
	testGetEarthRotationSpeed();
	testAddMobile();
	testAdvance();
	testCheckCollisions();
	testKillShip();
	testRemoveZombies();
}

void TestGame::testGetTimeInterval()
{
	// SETUP
	Game game = Game(TIME_INTERVAL, RADIUS, ROTATION_SPEED);

	// EXERCISE
	double t = Game::getTimeInterval();

	// VERIFY
	assert(TIME_INTERVAL == t);

}	// TEARDOWN

void TestGame::testGetEarthRadius()
{
	// SETUP
	// EXERCISE
	double radius = Game::getEarthRadius();

	// VERIFY
	assert(RADIUS == radius);

}	// TEARDOWN

void TestGame::testGetEarthPosition()
{
	// SETUP
	// EXERCISE
	Position ptEarth = Game::getEarthPosition();

	// VERIFY
	assert(Position() == ptEarth);

}	// TEARDOWN

void TestGame::testGetEarthRotationSpeed()
{
	// SETUP
	// EXERCISE
	double rotationSpeed = Game::getEarthRotationSpeed();

	// VERIFY
	assert(ROTATION_SPEED == rotationSpeed);

}	// TEARDOWN

void TestGame::testAddMobile()
{
	// SETUP
	Mobile* m = new Mobile(Position(1.0, 1.0), 0.0, 0.0);

	// EXERCISE
	Game::addMobile(m);

	// VERIFY
	assert(Game::mobileList.size() == 1);
	assert(Game::mobileList.front()->getPosition() == Position(1.0, 1.0));

	// TEARDOWN
	Game::mobileList = list<Mobile*>();
	delete m;
}

void TestGame::testAdvance()
{
	// SETUP
	Mobile* m = new Mobile(Position(0.0, 42164000), -3100, 0.0);
	Game::addMobile(m);

	// EXERCISE
	Game::advance();
	int x = (int)Game::mobileList.front()->getPosition().getMetersX();
	int y = (int)Game::mobileList.front()->getPosition().getMetersY();

	// VERIFY
	assert(x == -148800);
	assert(y == 42163482);

	// TEARDOWN
	Game::mobileList = list<Mobile*>();
	delete m;
}

void TestGame::testCheckCollisions()
{
	// SETUP
	Sputnik* sputnik = new Sputnik(Position(0.0, 10000000), 0.0, 0.0);		// Sputnik and GPS are 10.0m apart, radii add up to 16
	GPS* gps = new GPS(Position(10.0, 10000000), 0.0, 0.0);
	Hubble* hubble = new Hubble(Position(-20.0, 10000000), 0.0, 0.0);		// Hubble and Dragon 17.0m apart, radii add up to 17
	Dragon* dragon = new Dragon(Position(-37.0, 10000000), 0.0, 0.0);
	Starlink* starlink = new Starlink(Position(0.0, 6378006), 0.0, 0.0);	// starlink and earth, radii add up to 6378006

	GPScenter* piece = new GPScenter(Position(30.0, 10000000), 0.0, 0.0);	// this satellite piece is the only object safe from collision
																			// the piece and GPS are 20.0m apart, radii add up to 19.0

	Game::addMobile(sputnik);
	Game::addMobile(gps);
	Game::addMobile(hubble);
	Game::addMobile(dragon);
	Game::addMobile(starlink);
	Game::addMobile(piece);

	// EXERCISE
	Game::checkCollisions();

	// VERIFY
	assert(sputnik->isAlive() == false);
	assert(gps->isAlive() == false);
	assert(hubble->isAlive() == false);
	assert(dragon->isAlive() == false);
	assert(starlink->isAlive() == false);
	assert(piece->isAlive() == true);

	// TEARDOWN
	Game::mobileList = list<Mobile*>();
	delete sputnik;
	delete gps;
	delete hubble;
	delete dragon;
	delete starlink;
	delete piece;
}

void TestGame::testKillShip()
{
	// SETUP
	Ship* ship = new Ship(Position(), 0.0, 0.0);
	Game::ship = ship;

	// EXERCISE
	ship->kill();	// ship->kill() should call Game::killShip(), which sets Game::ship to nullptr
	
	// VERIFY
	assert(Game::ship == nullptr);

	// TEARDOWN
	Game::mobileList = list<Mobile*>();
	delete ship;
}

void TestGame::testRemoveZombies()
{
	// SETUP
	Mobile* m1 = new Mobile();
	Mobile* m2 = new Mobile();
	Mobile* m3 = new Mobile();

	Game::addMobile(m1);
	Game::addMobile(m2);
	Game::addMobile(m3);

	int startSize = Game::mobileList.size();

	m1->kill();
	m2->kill();

	// EXERCISE
	Game::removeZombies();

	// VERIFY
	assert(startSize == 3);
	assert(Game::mobileList.size() == 1);
	assert(m3->isAlive());

	// TEARDOWN
	Game::mobileList = list<Mobile*>();
	delete m3;
}
