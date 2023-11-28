#pragma once
#define PI 3.14159265359

#include <cmath>

using namespace std;

class Position;

class Trig {
public:
	static double computeSineComponent(double radians, double total);
	static double computeCosineComponent(double radians, double total);
	static double computeTotalComponent(double horizontalComponent, double verticalComponent);
	static double distanceBetweenPoints(Position startPt, Position endPt);
	static double getAngle(double dx, double dy);

};
