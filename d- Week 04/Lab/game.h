#include <list>

#include "piece.h"

#pragma once

class TestGame;

class Game {
	friend class TestGame;
public:
	static Piece* getPieceAt(Point point);
	static list<Point> getEnemyAttackSquares(Color yourColor);
	static list<Point> getCheckingPath() { return checkingPath; }

	static void addPiece(Piece * piece);
	static void toggleTurnHolder();

	static bool amIGuardingKing(Point point);
	static bool movePiece(Point from, Point to);
	static void draw(Point hoverPos, Point selectPos);

	static bool isCheckMate();
	static bool inCheck(Color yourColor);

	static void removeZombies();
	static void reset();
	static void newGame();

private:
	static void determineCheck();

	static list<Piece*> pieces;
	static Color currentTurnHolder;
	static Piece* kingInCheck;
	static list<Piece*> checkingPieces;
	static list<Point> checkingPath;
};
