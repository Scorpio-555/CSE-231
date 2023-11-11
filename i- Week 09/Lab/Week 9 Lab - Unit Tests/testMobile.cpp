#include "mobile.h"
#define TEST_POSITION Position(5.0, 5.0)

#include "testMobile.hpp"

void TestMobile::run() {
    testSputnik();
    testGPS();
    testHubble();
    testDragon();
    testStarlink();
    testGPSCenter();
    testShip();
}

void TestMobile::testSputnik() {
    Sputnik sputnik(TEST_POSITION, 0.0, 0.0);
    assert(sputnik.getRadius() == 4.0);
    assert(sputnik.getPosition().getX() == 5.0);
    assert(sputnik.getPosition().getY() == 5.0);
    assert(sputnik.getGravityDdx() == 0.0);
    assert(sputnik.getGravityDdy() == 0.0);
    assert(sputnik.isAlive() == true);
    sputnik.kill();
    assert(sputnik.isAlive() == false);
}

void TestMobile::testGPS() {
    GPS gps(TEST_POSITION, 0.0, 0.0);
    assert(gps.getRadius() == 12.0);
    assert(gps.getPosition().getX() == 5.0);
    assert(gps.getPosition().getY() == 5.0);
    assert(gps.getGravityDdx() == 0.0);
    assert(gps.getGravityDdy() == 0.0);
    assert(gps.isAlive() == true);
    gps.kill();
    assert(gps.isAlive() == false);
}

void TestMobile::testHubble() {
    Hubble hubble(TEST_POSITION, 0.0, 0.0);
    assert(hubble.getRadius() == 10.0);
    assert(hubble.getPosition().getX() == 5.0);
    assert(hubble.getPosition().getY() == 5.0);
    assert(hubble.getGravityDdx() == 0.0);
    assert(hubble.getGravityDdy() == 0.0);
    assert(hubble.isAlive() == true);
    hubble.kill();
    assert(hubble.isAlive() == false);
}

void TestMobile::testDragon() {
    Dragon dragon(TEST_POSITION, 0.0, 0.0);
    assert(dragon.getRadius() == 7.0);
    assert(dragon.getPosition().getX() == 5.0);
    assert(dragon.getPosition().getY() == 5.0);
    assert(dragon.getGravityDdx() == 0.0);
    assert(dragon.getGravityDdy() == 0.0);
    assert(dragon.isAlive() == true);
    dragon.kill();
    assert(dragon.isAlive() == false);

}

void TestMobile::testStarlink() {
    Starlink starlink(TEST_POSITION, 0.0, 0.0);
    assert(starlink.getRadius() == 6.0);
    assert(starlink.getPosition().getX() == 5.0);
    assert(starlink.getPosition().getY() == 5.0);
    assert(starlink.getGravityDdx() == 0.0);
    assert(starlink.getGravityDdy() == 0.0);
    assert(starlink.isAlive() == true);
    starlink.kill();
    assert(starlink.isAlive() == false);
}

void TestMobile::testGPSCenter() {
    GPScenter gpsCenter(TEST_POSITION, 0.0, 0.0);
    assert(gpsCenter.getRadius() == 7.0);
    assert(gpsCenter.getPosition().getX() == 5.0);
    assert(gpsCenter.getPosition().getY() == 5.0);
    assert(gpsCenter.getGravityDdx() == 0.0);
    assert(gpsCenter.getGravityDdy() == 0.0);
    assert(gpsCenter.isAlive() == true);
    gpsCenter.kill();
    assert(gpsCenter.isAlive() == false);
    
}

void TestMobile::testShip() {
    Ship ship(TEST_POSITION, 0.0, 0.0);
    assert(ship.getRadius() == 10.0);
    assert(ship.getPosition().getX() == 5.0);
    assert(ship.getPosition().getY() == 5.0);
    assert(ship.getGravityDdx() == 0.0);
    assert(ship.getGravityDdy() == 0.0);
    assert(ship.isAlive() == true);
    
}

