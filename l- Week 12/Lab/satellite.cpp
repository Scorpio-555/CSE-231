#include "satellite.h"
#include "uiDraw.h"
#include "game.h"

void Satellite::kill()
{
	Mobile::kill();
	spawnDebris();
}

void Satellite::spinWild()
{
	if (rotationSpeed > 0.0) {
		rotationSpeed = 0.15;
	}
	else {
		rotationSpeed = -0.15;
	}
}

void Satellite::spawnDebris()
{
	int totalCount = fragmentCount + parts.size();
	double rotationDegrees = 360.0 / totalCount;
	Angle a = Angle(rotationAngle.getDegrees() - debrisOffset);
	Velocity parentV = Velocity(dx, dy);

	for (Part* part : parts) {
		part->setPosition(getSpawnPosition(position, a));
		part->setAngle(rotationAngle);
		Velocity v = getSpawnVelocity(parentV, a);
		part->setDx(v.getDx());
		part->setDy(v.getDy());

		Game::addDebris(part);
		a.addDegrees(rotationDegrees);
	}

	for (int i = 0; i < fragmentCount; i++) {
		spawnFragment(position, a, parentV);
		a.addDegrees(rotationDegrees);
	}
}

void Satellite::activate()
{
	spinWild();
}

GPS::GPS(Position pt, double dx, double dy, Angle rotationAngle)
{
	alive = true;
	position = pt;
	this->dx = dx;
	this->dy = dy;
	radius = 12.0;
	this->rotationAngle = rotationAngle;
	rotationSpeed = -0.00701204819277108433734939759036;
	duration = random(300, 6000);

	debrisOffset = 180.0;
	fragmentCount = 2;
	parts = list<Part*>();
	parts.push_back(new GPSLeft());
	parts.push_back(new GPSCenter());
	parts.push_back(new GPSRight());
}

void GPS::draw()
{
	Position pt;
	ogstream gout(pt);
	gout.drawGPS(position, rotationAngle.getRadians());
}

Sputnik::Sputnik(Position pt, double dx, double dy) {
	alive = true;
	position = pt;
	this->dx = dx;
	this->dy = dy;
	radius = 4.0;
	rotationAngle = Angle();
	rotationSpeed = 0.05;
	duration = random(300, 5400);

	fragmentCount = 4;
	parts = list<Part*>();
}

void Sputnik::draw() {
	Position pt;
	ogstream gout(pt);
	gout.drawSputnik(position, rotationAngle.getRadians());
}

Hubble::Hubble(Position pt, double dx, double dy) {
	position = pt;
	this->dx = dx;
	this->dy = dy;
	radius = 10.0;
	rotationAngle = Angle();
	rotationSpeed = 0.0;
	duration = random(300, 3000);

	debrisOffset = 0.0;
	fragmentCount = 0;
	parts = list<Part*>();
	parts.push_back(new HubbleLeft());
	parts.push_back(new HubbleTelescope());
	parts.push_back(new HubbleRight());
	parts.push_back(new HubbleComputer());
}

void Hubble::draw() {
	Position pt;
	ogstream gout(pt);
	gout.drawHubble(position, rotationAngle.getRadians());
}

Dragon::Dragon(Position pt, double dx, double dy)
{
	position = pt;
	this->dx = dx;
	this->dy = dy;
	radius = 7.0;
	rotationAngle = Angle();
	rotationSpeed = -0.01;
	duration = random(300, 3000);

	debrisOffset = 0.0;
	fragmentCount = 2;
	parts = list<Part*>();
	parts.push_back(new CrewDragonLeft());
	parts.push_back(new CrewDragonCenter());
	parts.push_back(new CrewDragonRight());
}

void Dragon::draw()
{
	Position pt;
	ogstream gout(pt);
	gout.drawCrewDragon(position, rotationAngle.getRadians());
}

Starlink::Starlink(Position pt, double dx, double dy)
{
	position = pt;
	this->dx = dx;
	this->dy = dy;
	radius = 7.0;
	rotationAngle = Angle();
	rotationSpeed = -0.008;
	duration = random(300, 3000);

	debrisOffset = 90.0;
	fragmentCount = 2;
	parts = list<Part*>();
	parts.push_back(new StarlinkBody());
	parts.push_back(new StarlinkArray());
}

void Starlink::draw()
{
	Position pt;
	ogstream gout(pt);
	gout.drawStarlink(position, rotationAngle.getRadians());
}
