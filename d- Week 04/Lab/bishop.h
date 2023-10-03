#include "piece.h"

#pragma once

class Bishop : public Piece
{
public:
	Bishop(Color color, Point position);
	set<int> getAttackSquares();
	list<Point> getPossibleMoves();
	void draw();
};
