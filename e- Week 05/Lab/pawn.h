#include "piece.h"

#pragma once

class Pawn : public Piece
{
public:
	Pawn(Color color, Point point);

	set<int> getAttackSquares();
	list<Point> getPossibleMoves();

	static void resetPotentialEnPassant() { potentialEnPassant = Point(-1, -1); }

	bool jeopardizeKing(Point newPosition, bool iAmGuardingKing, bool inCheck);
	bool move(Point newPosition);
	void draw();
protected:
	void resurrect() { alive = true; }
private:
	static Point potentialEnPassant;
	int firstRank;
	int enPassantRank;
	int lastRank;
	int forwardBy;
};
