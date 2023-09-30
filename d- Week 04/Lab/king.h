#include "piece.h"

#pragma once

class King : public Piece
{
public:
    King(Color color, Point point);

    bool getHasMoved() { return hasMoved; }
    list<Point> getAttackSquares();
    list<Point> getPossibleMoves();

    void draw();
    bool move(Point point);

private:
    bool hasMoved;
};