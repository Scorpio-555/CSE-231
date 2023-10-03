#include "king.h"
#include "game.h"

King::King(Color color, Point point) {
    name = Name::KING;
    alive = true;
    hasMoved = false;
    this->color = color;
    this->position = point;
}

set<int> King::getAttackSquares() {
    return set<int>();
}

list<Point> King::getPossibleMoves() {
    set<int> enemyAttackSquares = Game::getEnemyAttackSquares(color);
    list<Point> possible = list<Point>();

    //castling
    if (hasMoved == false && Game::inCheck(color) == false) {
        /*// look for left rook
        leftCorner <-- position
        leftCorner.setX(0)
        leftCornerPiece <-- Game.getPieceAt(leftCorner)


        IF leftCornerPiece NOT NULL AND leftCornerPiece.getName() = "Rook"
            IF leftCornerPiece.getHasMoved() = FALSE
                leftOne <-- position
                leftOne.addX(-1)
                leftOneEmpty <-- (Game.getPieceAt(leftOne) = NULL)


                leftTwo <-- position
                leftTwo.addX(-2)
                leftTwoEmpty <-- (Game.getPieceAt(leftTwo) = NULL)


                leftOneSafe <-- leftOne NOT IN enemyAttackSquares
                leftTwoSafe <-- leftTwo NOT IN enemyAttackSquares


                bothEmpty <-- leftOneEmpty AND leftTwoEmpty
                bothSafe <-- leftOneSafe AND leftTwoSafe


                IF bothEmpty AND bothSafe
                    possible.insert(leftTwo) // queen's castle


        // look for left rook
        rightCorner <-- position
        rightCorner.setX(7)
        rightCornerPiece <-- Game.getPieceAt(rightCorner)


        IF rightCornerPiece NOT NULL AND rightCornerPiece.getName() = "Rook"
            IF rightCornerPiece.getHasMoved() = FALSE
                rightOne <-- position
                rightOne.addX(1)
                rightOneEmpty <-- (Game.getPieceAt(rightOne) = NULL)


                rightTwo <-- position
                rightTwo.addX(2)
                rightTwoEmpty <-- (Game.getPieceAt(rightTwo) = NULL)




                rightOneSafe <-- rightOne NOT IN enemyAttackSquares
                rightTwoSafe <-- rightTwo NOT IN enemyAttackSquares


                bothEmpty <-- rightOneEmpty AND rightTwoEmpty 
                bothSafe <-- rightOneSafe AND rightTwoSafe 


                IF bothEmpty AND bothSafe
                    possible.insert(rightTwo) // king's castle*/
    }

    list<Point> moves =
    {
        Point(-1, 1),  Point(0, 1),  Point(1, 1),
        Point(-1, 0),                Point(1, 0),
        Point(-1, -1), Point(0, -1), Point(1, -1)
    };

    for (Point move : moves) {
        Point point = position + move;
        if (point.inBounds()) {
            Piece* piece = Game::getPieceAt(point);
            bool isSafe = (enemyAttackSquares.find(point.getInt()) == enemyAttackSquares.end());

            if (isSafe && (piece == nullptr || piece->getColor() != color)) {
                possible.push_back(point);
            }
        }
    }

    return possible;
}

void King::draw()
{
}

bool King::move(Point point)
{
    return false;
}
