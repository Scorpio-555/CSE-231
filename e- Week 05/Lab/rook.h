#include "piece.h"

#pragma once

class Rook : public SlidingPiece
{
public:
	Rook(Color color, Point position);
	bool getHasMoved() { return hasMoved; }
	void castle() { position = castlePosition; hasMoved = true; }
	bool move(Point newPosition);
	void draw();
private:
	bool hasMoved;
	Point castlePosition;
};
