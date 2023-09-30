#include "piece.h"

#pragma once

class Pawn : public Piece
{
public:
	Pawn(Color color, Point point);
	
	list<Point> getAttackSquares();
	list<Point> getPossibleMoves();

	static void resetEnPotentialEnPassant() { potentialEnPassant = Point(-1,-1); }

	bool move(Point point);
	void draw();
private:
	static Point potentialEnPassant;
	int firstRank;
	int enPassantRank;
	int lastRank;
	int forwardBy;
};
