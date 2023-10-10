#include "king.h"
#include "rook.h"
#include "game.h"

King::King(Color color, Point point) {
    name = Name::KING;
    alive = true;
    hasMoved = false;
    this->color = color;
    this->position = point;
}

set<int> King::getAttackSquares() {
    set<int> attackSquares = set<int>();

    list<Point> moves =
    {
        Point(-1, 1),  Point(0, 1),  Point(1, 1),
        Point(-1, 0),                Point(1, 0),
        Point(-1, -1), Point(0, -1), Point(1, -1)
    };

    Point point = position;

    for (Point move : moves) {
        point = point + move;
        if (point.inBounds()) {
            attackSquares.insert(point.getInt());
        }
    }

    return attackSquares;
}

list<Point> King::getPossibleMoves() {
    set<int> enemyAttackSquares = Game::getEnemyAttackSquares(color);
    list<Point> possible = list<Point>();

    //castling
    if (hasMoved == false && Game::inCheck(color) == false) {
        // look for left rook
        Point leftCorner = position;
        leftCorner.setX(0);
        Rook* leftCornerPiece = (Rook*)Game::getPieceAt(leftCorner);
        if (leftCornerPiece && leftCornerPiece->getName() == ROOK) {
            if (!leftCornerPiece->getHasMoved()) {
                Point leftOne = position;
                leftOne.addX(-1);
                bool leftOneEmpty = (Game::getPieceAt(leftOne) == nullptr);
                Point leftTwo = position;
                leftTwo.addX(-2);
                bool leftTwoEmpty = (Game::getPieceAt(leftTwo) == nullptr);
                bool leftOneSafe = (enemyAttackSquares.find(leftOne.getInt()) == enemyAttackSquares.end());
                bool leftTwoSafe = (enemyAttackSquares.find(leftTwo.getInt()) == enemyAttackSquares.end());
                bool bothEmpty = leftOneEmpty && leftTwoEmpty;
                bool bothSafe = leftOneSafe && leftTwoSafe;
                if (bothEmpty && bothSafe) {
                    possible.push_back(leftTwo);// queen's castle
                }
            }
        }
        // look for right rook
        Point rightCorner = position;
        rightCorner.setX(7);
        Rook* rightCornerPiece = (Rook*)Game::getPieceAt(rightCorner);
        if (rightCornerPiece && rightCornerPiece->getName() == ROOK) {
            if (!rightCornerPiece->getHasMoved()) {
                Point rightOne = position;
                rightOne.addX(1);
                bool rightOneEmpty = (Game::getPieceAt(rightOne) == nullptr);
                Point rightTwo = position;
                rightTwo.addX(2);
                bool rightTwoEmpty = (Game::getPieceAt(rightTwo) == nullptr);
                bool rightOneSafe = enemyAttackSquares.find(rightOne.getInt()) == enemyAttackSquares.end();
                bool rightTwoSafe = enemyAttackSquares.find(rightTwo.getInt()) == enemyAttackSquares.end();
                bool bothEmpty = rightOneEmpty && rightTwoEmpty;
                bool bothSafe = rightOneSafe && rightTwoSafe;
                if (bothEmpty && bothSafe) {
                    possible.push_back(rightTwo);
                }
            }
        }
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
    ogstream gout;
    gout.drawKing(position.getInt(), color == Color::BLACK);
}

bool King::move(Point newPosition)
{
    Point oldPosition = position;
    bool moveSuccessful = Piece::move(newPosition);
    bool castling = (abs(position.getX() - oldPosition.getX()) == 2);

    if (moveSuccessful) {
        hasMoved = true;
    }

    // special king moves
    if (moveSuccessful && castling) {
        Rook* rook = nullptr;

        // queen's castle
        if (position.getX() == 2) {
            rook = (Rook*)Game::getPieceAt(Point(0, position.getY()));
        }
        // king's castle
        if (position.getX() == 6) {
            rook = (Rook*)Game::getPieceAt(Point(7, position.getY()));
        }

        rook->castle();
    }

    return moveSuccessful;
}
