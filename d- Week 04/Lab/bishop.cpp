#include "bishop.h"

Bishop::Bishop(Color color, Point position)
{
	name = Name::BISHOP;
	alive = true;
	this->color = color;
	this->position = position;
}

set<int> Bishop::getAttackSquares()
{
	return set<int>();
}

list<Point> Bishop::getPossibleMoves()
{
	return list<Point>();
}

void Bishop::draw()
{
}
