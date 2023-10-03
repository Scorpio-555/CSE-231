#include "knight.h"

Knight::Knight(Color color, Point position)
{
	name = Name::KNIGHT;
	alive = true;
	this->color = color;
	this->position = position;
}

set<int> Knight::getAttackSquares()
{
	return set<int>();
}

list<Point> Knight::getPossibleMoves()
{
	return list<Point>();
}

void Knight::draw()
{
}
