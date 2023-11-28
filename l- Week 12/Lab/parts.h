#pragma once

#include "mobile.h"
#include <list>

class Part : public Mobile {
public:
	Part() : Mobile() { fragmentCount = 0; }
	void kill();
	void setPosition(Position pt) { position = pt; }
	void setAngle(Angle angle) { rotationAngle = angle; }
	void setDx(double dx) { this->dx = dx; }
	void setDy(double dy) { this->dy = dy; }

protected:
	int fragmentCount;
};

class GPSCenter : public Part {
public:
	GPSCenter() : Part() { radius = 7.0; fragmentCount = 3; }
	void draw();
};

class GPSLeft : public Part {
public:
	GPSLeft() : Part() { radius = 8.0; fragmentCount = 3; }
	void draw();
};

class GPSRight : public Part {
public:
	GPSRight() : Part() { radius = 8.0; fragmentCount = 3; }
	void draw();
};

class HubbleTelescope : public Part {
public:
	HubbleTelescope() : Part() { radius = 10.0; fragmentCount = 3; }
	void draw();
};

class HubbleComputer : public Part {
public:
	HubbleComputer() : Part() { radius = 7.0; fragmentCount = 2; }
	void draw();
};

class HubbleLeft : public Part {
public:
	HubbleLeft() : Part() { radius = 8.0; fragmentCount = 2; }
	void draw();
};

class HubbleRight : public Part {
public:
	HubbleRight() : Part() { radius = 8.0; fragmentCount = 2; }
	void draw();
};

//

class CrewDragonCenter : public Part {
public:
	CrewDragonCenter() : Part() { radius = 6.0; fragmentCount = 4; }
	void draw();
};

class CrewDragonLeft : public Part {
public:
	CrewDragonLeft() : Part() { radius = 6.0; fragmentCount = 2; }
	void draw();
};

class CrewDragonRight : public Part {
public:
	CrewDragonRight() : Part() { radius = 6.0; fragmentCount = 2; }
	void draw();
};

//

class StarlinkBody : public Part {
public:
	StarlinkBody() : Part() { radius = 2.0; fragmentCount = 3; }
	void draw();
};

class StarlinkArray : public Part {
public:
	StarlinkArray() : Part() { radius = 4.0; fragmentCount = 3; }
	void draw();
};
