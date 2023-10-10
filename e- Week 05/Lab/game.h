#include <list>
#include <set>
#include "piece.h"

#pragma once

class Game {
public:
	static Color getTurnHolder() { return currentTurnHolder; }
	static Piece* getPieceAt(Point point);
	static Piece* getKing(Color color);
	static set<int> getEnemyAttackSquares(Color yourColor);
	static set<int> getCheckingPath() { return checkingPath; }

	static void addPiece(Piece* piece);
	static void toggleTurnHolder();

	static bool amIGuardingKing(Point point);
	static Point getDirection(Point startingPoint, Point secondPoint);
	static bool movePiece(Point from, Point to);
	static void draw(int hoverPos, int selectPos);

	static bool isEndGame();
	static bool inCheck(Color yourColor);
	static bool isCheckmate() { return checkmate; }
	static bool isStalemate() { return stalemate; }

	static void removeZombies();
	static void reset();
	static void newGame();

private:
	static void determineCheck();

	static list<Piece*> pieces;
	static Color currentTurnHolder;
	static Piece* kingInCheck;
	static list<Piece*> checkingPieces;
	static set<int> checkingPath;
	static bool checkmate;
	static bool stalemate;
};
