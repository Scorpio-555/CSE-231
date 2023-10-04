#include "piece.h"

#pragma once

class Queen : public SlidingPiece
{
public:
	Queen(Color color, Point position);
	void draw();
};

