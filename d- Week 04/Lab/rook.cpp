#include "rook.h"
#include "game.h"

Rook::Rook(Color color, Point position)
{
	name = Name::ROOK;
	alive = true;
	this->color = color;
	this->position = position;
	hasMoved = false;
	if (position.getX() == 0) {
		castlePosition = Point(3, position.getY());
	}
	else {
		castlePosition = Point(5, position.getY());
	}
}

set<int> Rook::getAttackSquares()
{
	set<int> attackSquares = set<int>();

	list<Point> moves =
	{
				     Point(0,  1),
	   Point(-1, 0),              Point(1, 0),
				     Point(0, -1)
	};

	for (Point move : moves) {
		Point point = position + move;
		bool done = false;
		bool checkingKing = false;
		Piece* piece;

		while (!done) {
			piece = Game::getPieceAt(point);

			if (checkingKing) {
				done = true;
			}

			if (point.inBounds() == false) {				// hit the edge of board
				done = true;
			}
			else if (piece != nullptr && checkingKing == false) {	// came across a game piece
				checkingKing = (piece->getName() == Name::KING && piece->getColor() != color);
				done = !checkingKing;
				attackSquares.insert(point.getInt());
				point = point + move;
			}
			else {													// found an empty game square
				attackSquares.insert(point.getInt());
				point = point + move;
			}
		}
	}

	return attackSquares;
}

list<Point> Rook::getPossibleMoves()
{
	return list<Point>();
}

void Rook::draw()
{
}
