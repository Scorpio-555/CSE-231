#pragma once
#include "angle.h"
#include "position.h"

class Earth {
public:
	Earth() : radius(0.0), rotationSpeed(0.0) {
		angle = Angle();
		position = Position();
	}
	Earth(double radius, double rotationSpeed) : radius(radius), rotationSpeed(rotationSpeed), angle(Angle()), position(Position()) {}
	Earth(double radius, double rotationSpeed, Angle angle, Position position) : radius(radius), rotationSpeed(rotationSpeed), angle(angle), position(position) {}
	double getRadius() { return radius; }
	Position getPosition() { return position; }
	double getRotationSpeed() { return rotationSpeed; }
	double getAngle() { return angle.getRadians(); };
	void rotate() { angle.addRadians(rotationSpeed); }
private:
	Angle angle;
	Position position;
	double rotationSpeed;
	double radius;
};
