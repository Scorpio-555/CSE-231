#include "angle.h"

double Angle::getDegrees() const
{
	return convertToDegrees(radians);
}

double Angle::getRadians() const
{
	return radians;
}

void Angle::setDegrees(double degrees)
{
	radians = normalize(convertToRadians(degrees));
}

void Angle::setRadians(double radians)
{
	this->radians = normalize(radians);
}

void Angle::addRadians(double radians)
{
	setRadians(getRadians() + radians);
}

void Angle::addDegrees(double degrees)
{
	setDegrees(getDegrees() + degrees);
}

Angle& Angle::operator=(const Angle& rhs)
{
	radians = rhs.getRadians();
	return *this;
}

bool Angle::operator==(const Angle& rhs) const
{
	return radians == rhs.getRadians();
}

bool Angle::operator!=(const Angle& rhs) const
{
	return radians != rhs.getRadians();
}

Angle Angle::operator-()
{
	return Angle(360.0 - radians);
}

ostream& Angle::operator<<(ostream& out)
{
	display(out);
	return out;
}

void Angle::display(ostream& out) const
{
	out.precision(1);
	out.setf(ios::fixed | ios::showpoint);
	out << getDegrees() << "degrees";
}

double Angle::convertToDegrees(double radians) const
{
	return normalize(radians) / TWO_PI * 360.0;
}

double Angle::convertToRadians(double degrees) const
{
	return normalize(degrees / 360.0 * TWO_PI);
}

double Angle::normalize(double radians) const
{
	if (radians >= TWO_PI)
	{
		double multiples = floor(radians / TWO_PI);
		assert(radians - TWO_PI * multiples >= 0.0);
		assert(radians - TWO_PI * multiples <= TWO_PI);
		return radians - (TWO_PI * multiples);
	}
	else if (radians < 0.0)
	{
		double multiples = ceil(-radians / TWO_PI);
		assert(TWO_PI * multiples + radians >= 0.0);
		assert(TWO_PI * multiples + radians <= TWO_PI);
		return TWO_PI * multiples + radians;
	}

	assert(0.0 <= radians && radians <= TWO_PI);
	return radians;
}
