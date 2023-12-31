#include <string>
#include <list>
#include "enum.h"
#include "point.h"

#pragma once

using namespace std;

class Piece
{
public:

	// getters
	Name getName() { return name; }
	Point getPosition() { return position; }
	Color getColor() { return color; }
	bool isAlive() { return alive; }

	//setters
	void kill() { alive = false; }

	// virtual functions
	virtual bool move(Point newPosition);

	// pure virtual functions
	virtual list<Point> getAttackSquares() = 0;
	virtual list<Point> getPossibleMoves() = 0;
	virtual void draw() = 0;
protected:
	Name name;
	Color color;
	Point position;
	bool alive;
};
