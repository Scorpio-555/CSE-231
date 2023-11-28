#pragma once

#include"position.h"
#include "angle.h"
#include "uiDraw.h"
#include "trig.h"

class Mobile {
public:
	Mobile() : dx(0.0), dy(0.0), alive(true), radius(0.0), position(Position()), rotationAngle(Angle()), rotationSpeed(0.0) {}
	Mobile(Position pt, double dx, double dy) : dx(dx), dy(dy), alive(true), radius(0.0), position(pt), rotationAngle(Angle()), rotationSpeed(0.0) {}
	Position getPosition();
	double getRadius();
	double getHeight();
	double get_gH();
	double getGravityDdx();
	double getGravityDdy();
	bool isAlive();
	virtual void kill();
	virtual void move();
	virtual void draw() = 0;

protected:
	double dx;
	double dy;
	bool alive;
	double radius;
	Position position;
	Angle rotationAngle;
	double rotationSpeed;
};

void spawnFragment(Position pt, Angle a, Velocity v);
Position getSpawnPosition(Position pt, Angle a);
Velocity getSpawnVelocity(Velocity parentV, Angle a);

class Timed : public Mobile {
public:
	Timed() : Mobile() { duration = 0; }
	void move();
protected:
	int duration;
	void countDown();
	virtual void activate();
};

class Fragment : public Timed {
public:
	Fragment(Position pt, double dx, double dy);
	void draw();
};

class Ship : public Mobile {
public:
	Ship(Position pt, double dx, double dy);
	void move();
	void setThrusterLeft(bool status);
	void setThrusterRight(bool status);
	void setThrusterMain(bool status);
	void fire();
	void kill();
	void draw();
private:
	double thrustAcceleration;
	bool thrusterLeft;
	bool thrusterRight;
	bool thrusterMain;
};

class Bullet : public Timed {
public:
	Bullet(Position pt, double dx, double dy);
	void draw();
};
