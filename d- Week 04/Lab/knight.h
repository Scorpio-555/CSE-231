#include "piece.h"

#pragma once

class Knight : public Piece
{
public:
	Knight(Color color, Point position);
	set<int> getAttackSquares();
	list<Point> getPossibleMoves();
	void draw();
};
