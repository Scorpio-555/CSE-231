#include "piece.h"
#include "game.h"
#include <cassert>

bool Piece::jeopardizeKing(Point newPosition, bool iAmGuardingKing, bool inCheck)
{
    // we either aren't in check, or we want to move to a square that gets us out of check
    if (inCheck == false || Game::getCheckingPath().find(newPosition.getInt()) != Game::getCheckingPath().end()) {
        // our movement has the potential to put the king in check
        if (iAmGuardingKing) {
            Point kingPoint = Game::getKing(color)->getPosition();
            Point directionToKing = Game::getDirection(position, kingPoint);
            Point directionAwayFromKing = Game::getDirection(kingPoint, position);
            Point desiredDirection = Game::getDirection(position, newPosition);
            // we can only move directly toward the king, or directly away, otherwise we will put the king in check
            return (desiredDirection == directionToKing || desiredDirection == directionAwayFromKing);
        }
        // we have no potential to put the king in check
        else {
            return false;
        }
    }
    // we are in check and the square we want to move to will not get us out of check
    else {
        return true;
    }
}

bool Piece::move(Point newPosition)
{
    bool moveFound = false;

    for (Point point : getPossibleMoves()) {
        if (newPosition == point) {
            moveFound = true;
        }
    }

    if (moveFound) {
        Piece* piece = Game::getPieceAt(newPosition);

        if (piece != nullptr) {
            if (piece->getName() != Name::KING) {
                piece->kill();
            }
            else {
                return false;
            }
        }

        position = newPosition;

        return true;
    }

    return false;
}

set<int> SlidingPiece::getAttackSquares()
{
    set<int> attackSquares = set<int>();

    for (Point move : moveList) {
        Point point = position + move;
        bool done = false;
        bool checkingKing = false;
        Piece* piece;

        while (!done) {
            piece = Game::getPieceAt(point);

            if (checkingKing) {
                done = true;
            }

            if (point.inBounds() == false) {						// hit the edge of board
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

list<Point> SlidingPiece::getPossibleMoves()
{
    list<Point> possible;
    bool guardingKing = Game::amIGuardingKing(getPosition());
    bool inCheck = Game::inCheck(color);

    for (Point move : moveList) {
        Point point = position;
        Piece* piece;
        do {
            point = point + move;
            piece = Game::getPieceAt(point);
            if (jeopardizeKing(point, guardingKing, inCheck) == false) {
                if (piece == nullptr || piece->getColor() != color) {
                    possible.push_back(point);
                }
            }
        } while (point.inBounds() && piece == nullptr);
    }

	return possible;
}
