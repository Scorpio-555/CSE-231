#include "piece.h"
#include "game.h"

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
    /*bool moveFound = false;

    for (Point point : getPossibleMoves()) {
        if (newPosition.getInt() == point.getInt()) {
            moveFound = true;
        }
    }

    if (moveFound) {
        Piece* target = Game::getPieceAt(newPosition);
        bool targetIsEmpty = (target == nullptr);

        if (targetIsEmpty == false) {
            if (target->getName() != Name::KING) {
                target->kill();
            }
            else {
                return false;
            }
        }

        position = newPosition;

        return true;
    }

    return false;*/

    position = newPosition;
    return true;
}
