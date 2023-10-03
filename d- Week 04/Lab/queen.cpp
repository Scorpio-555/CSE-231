#include "queen.h"

Queen::Queen(Color color, Point position)
{
	name = Name::QUEEN;
	alive = true;
	this->color = color;
	this->position = position;
}

set<int> Queen::getAttackSquares()
{
	return set<int>();
}

list<Point> Queen::getPossibleMoves()
{
	return list<Point>();
}

void Queen::draw()
{
}
