#include "king.h"

King::King(Color color, Point point) {
    name = Name::KING;
    alive = true;
    hasMoved = false;
    this->color = color;
    this->position = point;
}

list<Point> King::getAttackSquares() {
    return list<Point>();
}

list<Point> King::getPossibleMoves() {
    return list<Point>();
}

void King::draw()
{
}

bool King::move(Point point)
{
    return false;
}
