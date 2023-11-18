#include "mobile.h"
#define TEST_POSITION Position(0.0, 6378000.0)

#include "testMobile.h"

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

    // SETUP
    Sputnik sputnik(TEST_POSITION, 0.0, 0.0);

    // EXERCISE
    bool beforeKill = sputnik.isAlive();
    sputnik.kill();
    bool afterKill = sputnik.isAlive();

    // VERIFY
    assert(sputnik.getRadius() == 4.0);
    assert(sputnik.getPosition().getMetersX() == 0.0);
    assert(sputnik.getPosition().getMetersY() == 6378000.0);
    assert(sputnik.getGravityDdx() == 0.0);
    assert(sputnik.getGravityDdy() == -9.8067);
    assert(beforeKill == true);
    assert(afterKill == false);

}   // TEARDOWN

void TestMobile::testGPS() {
    // SETUP
    GPS gps(TEST_POSITION, 0.0, 0.0);

    // EXERCISE
    bool beforeKill = gps.isAlive();
    gps.kill();
    bool afterKill = gps.isAlive();

    // VERIFY
    assert(gps.getRadius() == 12.0);
    assert(gps.getPosition().getMetersX() == 0.0);
    assert(gps.getPosition().getMetersY() == 6378000.0);
    assert(gps.getGravityDdx() == 0.0);
    assert(gps.getGravityDdy() == -9.8067);
    assert(beforeKill == true);
    assert(afterKill == false);

}   // TEARDOWN

void TestMobile::testHubble() {
    // SETUP
    Hubble hubble(TEST_POSITION, 0.0, 0.0);

    // EXERCISE
    bool beforeKill = hubble.isAlive();
    hubble.kill();
    bool afterKill = hubble.isAlive();

    // VERIFY
    assert(hubble.getRadius() == 10.0);
    assert(hubble.getPosition().getMetersX() == 0.0);
    assert(hubble.getPosition().getMetersY() == 6378000.0);
    assert(hubble.getGravityDdx() == 0.0);
    assert(hubble.getGravityDdy() == -9.8067);
    assert(beforeKill == true);
    assert(afterKill == false);

}   // TEARDOWN

void TestMobile::testDragon() {
    // SETUP
    Dragon dragon(TEST_POSITION, 0.0, 0.0);

    // EXERCISE
    bool beforeKill = dragon.isAlive();
    dragon.kill();
    bool afterKill = dragon.isAlive();

    // VERIFY
    assert(dragon.getRadius() == 7.0);
    assert(dragon.getPosition().getMetersX() == 0.0);
    assert(dragon.getPosition().getMetersY() == 6378000.0);
    assert(dragon.getGravityDdx() == 0.0);
    assert(dragon.getGravityDdy() == -9.8067);
    assert(beforeKill == true);
    assert(afterKill == false);

}   // TEARDOWN

void TestMobile::testStarlink() {
    // SETUP
    Starlink starlink(TEST_POSITION, 0.0, 0.0);

    // EXERCISE
    bool beforeKill = starlink.isAlive();
    starlink.kill();
    bool afterKill = starlink.isAlive();

    // VERIFY
    assert(starlink.getRadius() == 6.0);
    assert(starlink.getPosition().getMetersX() == 0.0);
    assert(starlink.getPosition().getMetersY() == 6378000.0);
    assert(starlink.getGravityDdx() == 0.0);
    assert(starlink.getGravityDdy() == -9.8067);
    assert(beforeKill == true);
    assert(afterKill == false);

}   // TEARDOWN

void TestMobile::testGPSCenter() {
    // SETUP
    GPScenter gpsCenter(TEST_POSITION, 0.0, 0.0);

    // EXERCISE
    bool beforeKill = gpsCenter.isAlive();
    gpsCenter.kill();
    bool afterKill = gpsCenter.isAlive();

    // VERIFY
    assert(gpsCenter.getRadius() == 7.0);
    assert(gpsCenter.getPosition().getMetersX() == 0.0);
    assert(gpsCenter.getPosition().getMetersY() == 6378000.0);
    assert(gpsCenter.getGravityDdx() == 0.0);
    assert(gpsCenter.getGravityDdy() == -9.8067);
    assert(beforeKill == true);
    assert(afterKill == false);

}   // TEARDOWN

void TestMobile::testShip() {
    // SETUP
    Ship ship(TEST_POSITION, 0.0, 0.0);

    // EXERCISE
    bool beforeKill = ship.isAlive();
    ship.kill();
    bool afterKill = ship.isAlive();

    // VERIFY
    assert(ship.getRadius() == 10.0);
    assert(ship.getPosition().getMetersX() == 0.0);
    assert(ship.getPosition().getMetersY() == 6378000.0);
    assert(ship.getGravityDdx() == 0.0);
    assert(ship.getGravityDdy() == -9.8067);
    assert(beforeKill == true);
    assert(afterKill == false);

}   // TEARDOWN
