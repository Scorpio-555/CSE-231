#pragma once

#include"position.h"
#include "angle.h"

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

protected:
	double dx;
	double dy;
	bool alive;
	double radius;
	Position position;
	Angle rotationAngle;
	double rotationSpeed;
};

class Sputnik : public Mobile{
public:
	Sputnik(Position pt, double dx, double dy) : Mobile() {
		position = pt;
		this->dx = dx;
		this->dy = dy;
		radius = 4.0;
	}
};

class GPS : public Mobile {
public:
	GPS(Position pt, double dx, double dy) : Mobile() {
		position = pt;
		this->dx = dx;
		this->dy = dy;
		radius = 12.0;
	}
};

class Hubble : public Mobile {
public:
	Hubble(Position pt, double dx, double dy) : Mobile() {
		position = pt;
		this->dx = dx;
		this->dy = dy;
		radius = 10.0;
	}
};

class Dragon : public Mobile {
public:
	Dragon(Position pt, double dx, double dy) : Mobile() {
		position = pt;
		this->dx = dx;
		this->dy = dy;
		radius = 7.0;
	}
};

class Starlink : public Mobile {
public:
	Starlink(Position pt, double dx, double dy) : Mobile() {
		position = pt;
		this->dx = dx;
		this->dy = dy;
		radius = 6.0;
	}
};

class GPScenter : public Mobile {
public:
	GPScenter(Position pt, double dx, double dy) : Mobile() {
		position = pt;
		this->dx = dx;
		this->dy = dy;
		radius = 7.0;
	}
};

class Ship : public Mobile {
public:
	Ship(Position pt, double dx, double dy) : Mobile() {
		position = pt;
		this->dx = dx;
		this->dy = dy;
		radius = 10.0;
	}
};
