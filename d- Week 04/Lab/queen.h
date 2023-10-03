#include "piece.h"

#pragma once

class Queen : public Piece
{
public:
	Queen(Color color, Point position);
	set<int> getAttackSquares();
	list<Point> getPossibleMoves();
	void draw();
};

