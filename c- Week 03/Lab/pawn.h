#include "piece.h"

#pragma once

class Pawn : public Piece
{
public:
	Pawn(Color color, Point point);
	bool move(Point point);
	list<Point> getAttackSquares();
	list<Point> getPossibleMoves();
	void draw();
private:
	int firstRank;
	int enPassantRank;
	int lastRank;
	int forwardBy;
};
