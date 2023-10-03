#include "piece.h"

#pragma once

class Rook : public Piece
{
public:
	Rook(Color color, Point position);
	set<int> getAttackSquares();
	list<Point> getPossibleMoves();
	bool getHasMoved() { return hasMoved; }
	void castle() { position = castlePosition; hasMoved = true; }
	void draw();
private:
	bool hasMoved;
	Point castlePosition;
};
