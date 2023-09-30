#include "piece.h"
#include "game.h"

bool Piece::move(Point newPosition)
{
    bool moveFound = false;

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

    return false;
}
