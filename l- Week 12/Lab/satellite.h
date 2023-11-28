
#pragma once

#include "mobile.h"
#include "parts.h"

class Satellite : public Timed {
public:
	void kill();
protected:
	void spinWild();
	void spawnDebris();
	void activate();

	double debrisOffset;
	int fragmentCount;
	list<Part*> parts;
};

class GPS : public Satellite {
public:
	GPS(Position pt, double dx, double dy, Angle rotationAngle);
	void draw();
};

class Sputnik : public Satellite {
public:
	Sputnik(Position pt, double dx, double dy);
	void draw();
};

class Hubble : public Satellite {
public:
	Hubble(Position pt, double dx, double dy);
	void draw();
};

class Dragon : public Satellite {
public:
	Dragon(Position pt, double dx, double dy);
	void draw();
};

class Starlink : public Satellite {
public:
	Starlink(Position pt, double dx, double dy);
	void draw();
};
