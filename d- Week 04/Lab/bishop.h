#include "piece.h"

#pragma once

class Bishop : public SlidingPiece
{
public:
	Bishop(Color color, Point position);
	void draw();
};
