#include "pawn.h"

Pawn::Pawn(Color color, Point point)
{
    name = Name::PAWN;
    alive = true;
    this->color = color;
    this->position = position;

    if (color == Color::WHITE) {
        firstRank = 1;
        enPassantRank = 4;
        lastRank = 7;
        forwardBy = 1;
    }
    else {
        firstRank = 6;
        enPassantRank = 3;
        lastRank = 0;
        forwardBy = -1;
    }
}

bool Pawn::move(Point point)
{
	return false;
}

list<Point> Pawn::getAttackSquares()
{
	return list<Point>();
}

list<Point> Pawn::getPossibleMoves()
{
	return list<Point>();
}

void Pawn::draw()
{
}
