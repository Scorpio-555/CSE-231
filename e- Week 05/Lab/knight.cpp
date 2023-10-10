#include "knight.h"
#include "game.h"

Knight::Knight(Color color, Point position)
{
	name = Name::KNIGHT;
	alive = true;
	this->color = color;
	this->position = position;
}

set<int> Knight::getAttackSquares()
{
	set<int> attackSquares = set<int>();

	list<Point> moves =
	{
				 Point(-1, 2),		  Point(1, 2),
		Point(-2, 1),				   		   Point(2, 1),

		Point(-2, -1),				   		   Point(2, -1),
				 Point(-1, -2),		  Point(1, -2)
	};

	for (Point move : moves) {
		Point point = position + move;
		if (point.inBounds()) {
			attackSquares.insert(point.getInt());
		}
	}

	return attackSquares;
}

list<Point> Knight::getPossibleMoves()
{
	list<Point> possible = list<Point>();
	set<int> attackSquares = getAttackSquares();
	bool guardingKing = Game::amIGuardingKing(getPosition());
	bool inCheck = Game::inCheck(color);

	for (int square : attackSquares) {
		if (jeopardizeKing(Point(square), guardingKing, inCheck) == false) {
			Piece* piece = Game::getPieceAt(Point(square));
			if (piece == nullptr || piece->getColor() != color) {
				possible.push_back(Point(square));
			}
		}
	}

	return possible;
}

void Knight::draw()
{
	ogstream gout;
	gout.drawKnight(position.getInt(), color == Color::BLACK);
}
