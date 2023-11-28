#include "parts.h"

void Part::kill()
{
	Mobile::kill();

	Angle a = Angle(random(0.0, 360.0));
	double rotationDegress = 360.0 / fragmentCount;
	for (int i = 0; i < fragmentCount; i++) {
		spawnFragment(position, a, Velocity(dx, dy));
		a.addDegrees(rotationDegress);
	}
}

void GPSCenter::draw()
{
	Position pt;
	ogstream gout(pt);
	gout.drawGPSCenter(position, rotationAngle.getRadians());
}

void GPSLeft::draw()
{
	Position pt;
	ogstream gout(pt);
	gout.drawGPSLeft(position, rotationAngle.getRadians());
}

void GPSRight::draw()
{
	Position pt;
	ogstream gout(pt);
	gout.drawGPSRight(position, rotationAngle.getRadians());
}

void HubbleTelescope::draw()
{
	Position pt;
	ogstream gout(pt);
	gout.drawHubbleTelescope(position, rotationAngle.getRadians());
}

void HubbleLeft::draw()
{
	Position pt;
	ogstream gout(pt);
	gout.drawHubbleLeft(position, rotationAngle.getRadians());
}

void HubbleRight::draw()
{
	Position pt;
	ogstream gout(pt);
	gout.drawHubbleRight(position, rotationAngle.getRadians());
}

void HubbleComputer::draw()
{
	Position pt;
	ogstream gout(pt);
	gout.drawHubbleComputer(position, rotationAngle.getRadians());
}

void CrewDragonCenter::draw()
{
	Position pt;
	ogstream gout(pt);
	gout.drawCrewDragonCenter(position, rotationAngle.getRadians());
}

void CrewDragonLeft::draw()
{
	Position pt;
	ogstream gout(pt);
	gout.drawCrewDragonLeft(position, rotationAngle.getRadians());
}

void CrewDragonRight::draw()
{
	Position pt;
	ogstream gout(pt);
	gout.drawCrewDragonRight(position, rotationAngle.getRadians());
}

void StarlinkBody::draw()
{
	Position pt;
	ogstream gout(pt);
	gout.drawStarlinkBody(position, rotationAngle.getRadians());
}

void StarlinkArray::draw()
{
	Position pt;
	ogstream gout(pt);
	gout.drawStarlinkArray(position, rotationAngle.getRadians());
}
