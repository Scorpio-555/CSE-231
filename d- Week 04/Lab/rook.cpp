#include "rook.h"
#include "game.h"
#include <cassert>

Rook::Rook(Color color, Point position)
{
	name = Name::ROOK;
	alive = true;
	this->color = color;
	this->position = position;
	hasMoved = false;
	if (position.getX() == 0) {
		castlePosition = Point(3, position.getY());
	}
	else {
		castlePosition = Point(5, position.getY());
	}

	moveList = 
	{
			        Point(0,  1),
		Point(-1, 0),			Point(1, 0),
		    	    Point(0, -1)
	};
}

bool Rook::move(Point newPosition)
{
	bool moveSuccessful = Piece::move(newPosition);
	if (moveSuccessful) {
		hasMoved = true;
	}
	return moveSuccessful;
}

void Rook::draw()
{
}
