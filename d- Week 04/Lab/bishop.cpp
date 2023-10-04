#include "bishop.h"
#include "game.h"

Bishop::Bishop(Color color, Point position)
{
	name = Name::BISHOP;
	alive = true;
	this->color = color;
	this->position = position;
	moveList =
	{
		Point(-1, 1),				Point(1,  1),

		Point(-1, -1),              Point(1, -1)
	};
}

void Bishop::draw()
{
}
