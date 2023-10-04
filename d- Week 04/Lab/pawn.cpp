#include "pawn.h"
#include "game.h"

Point Pawn::potentialEnPassant = Point(-1, -1);

Pawn::Pawn(Color color, Point position)
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

bool Pawn::jeopardizeKing(Point newPosition, bool iAmGuardingKing, bool inCheck)
{
    Piece* target = Game::getPieceAt(newPosition);
    Piece* behindEnPassant = Game::getPieceAt(Point(newPosition.getX(), newPosition.getY() - forwardBy));
    Piece* king = Game::getKing(color);
    set<int> checkingPath = Game::getCheckingPath();
    bool enPassant = (position.getX() != newPosition.getX() && target == nullptr);
    bool onKingsRow = (position.getY() == king->getPosition().getY());
    bool enemyPawnChecking = (enPassant && checkingPath.find(behindEnPassant->getPosition().getInt()) != checkingPath.end());

    // there is a weird exception if we perform en passant and are on same row as king
    if (inCheck == false && enPassant && onKingsRow) {
        Pawn* enemyPawn = (Pawn*)behindEnPassant;
        enemyPawn->kill();
        iAmGuardingKing = Game::amIGuardingKing(position);
        enemyPawn->resurrect();
    }

    // we either aren't in check, or we want to move to a square that gets us out of check
    if (inCheck == false || checkingPath.find(newPosition.getInt()) != checkingPath.end() || enemyPawnChecking) { 

        // our movement has the potential to put the king in check
        if (iAmGuardingKing) {
            Point kingPoint = king->getPosition();
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

bool Pawn::move(Point newPosition)
{/*
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

        // for promotion, FIRST call pawn.kill() THEN addPiece(Queen)

        return true;
    }

    return false;*/
    position = newPosition;
    return true;
}

set<int> Pawn::getAttackSquares()
{
    Point point = position;
    set<int> attackSquares = set<int>();
    list<Point> moves = { Point(-1, forwardBy), Point(1, forwardBy) };
    for (Point move : moves) {
        point = point + move;
        if (point.inBounds()) {
            attackSquares.insert(point.getInt());
        }
    }
	return attackSquares;
}

list<Point> Pawn::getPossibleMoves()
{
    return list<Point>();
}

void Pawn::draw()
{
}
