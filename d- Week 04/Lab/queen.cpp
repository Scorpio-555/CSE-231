#include "queen.h"
#include "game.h"

Queen::Queen(Color color, Point position)
{
	name = Name::QUEEN;
	alive = true;
	this->color = color;
	this->position = position;
	moveList =
	{
		Point(-1, 1),  Point(0, 1),  Point(1, 1),
		Point(-1, 0),                Point(1, 0),
		Point(-1, -1), Point(0, -1), Point(1, -1)
	};
}

void Queen::draw()
{
}
