#include "trig.h"
#include "position.h"

double Trig::computeSineComponent(double radians, double total)
{
	return total * sin(radians);
}

double Trig::computeCosineComponent(double radians, double total)
{
	return total * cos(radians);
}

double Trig::computeTotalComponent(double horizontalComponent, double verticalComponent)
{
	return sqrt(pow(horizontalComponent, 2) + pow(verticalComponent, 2));
}

double Trig::distanceBetweenPoints(Position startPt, Position endPt)
{
	return sqrt(pow((endPt.getMetersX() - startPt.getMetersX()), 2) + pow((endPt.getMetersY() - startPt.getMetersY()), 2));
}

double Trig::getAngle(double dx, double dy)
{
	return atan2(dx, dy);
}
