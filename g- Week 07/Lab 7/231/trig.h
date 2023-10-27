#pragma once
#define PI 3.14159265359

#include <cmath>

using namespace std;
#include "position.h"

class Trig {
public:
	static double computeVerticalComponent(double radians, double total) { return total * sin(radians); }
	static double computeHorizontalComponent(double radians, double total) { return total * cos(radians); }
	static double computeTotalComponent(double horizontalComponent, double verticalComponent) { return sqrt(pow(horizontalComponent, 2) + pow(verticalComponent, 2)); }
	/*static double distanceBetweenPoints(Position startPt, Position endPt) { return sqrt(pow((endPt.getMetersX() - startPt.getMetersX()), 2) + pow((endPt.getMetersY() - startPt.getMetersY()), 2)); }*/
	static double distanceBetweenPoints(Position startPt, Position endPt) { 
		double distance = 0.0;
		double x1 = startPt.getMetersX();
		double y1 = startPt.getMetersY();
		double x2 = endPt.getMetersX();
		double y2 = endPt.getMetersY();

		distance = sqrt(pow((endPt.getMetersX() - startPt.getMetersX()), 2) + pow((endPt.getMetersY() - startPt.getMetersY()), 2));

		return distance; 
	}
	static double areaOfCircle(double radius) { return PI * radius * radius; }
	static double getAngle(double dx, double dy) { return atan2(dx, dy); }

};
