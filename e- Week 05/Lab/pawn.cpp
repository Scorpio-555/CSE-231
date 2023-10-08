#include "pawn.h"
#include "game.h"
#include "queen.h"

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
{
	Point oldPosition = position;
    Piece* target = Game::getPieceAt(newPosition);
    bool emptyTarget = (target == nullptr);
    bool moveSuccessful = Piece::move(newPosition);

    if(moveSuccessful){
        // if we moved diagonally into an empty square, kill via en passant
        if (position.getX() != oldPosition.getX() && emptyTarget) {
            Piece* enemyPawn = Game::getPieceAt(potentialEnPassant);
            enemyPawn->kill();
        }

        // if we moved two squares, there is a potential for opponent en passant
        if (abs(position.getY() - oldPosition.getY()) == 2) {
            potentialEnPassant = position;
        }
        // en passant was either performed or forfeit. It's no longer an option
        else {
            resetPotentialEnPassant();
        }

        // promotion
        if (position.getY() == lastRank) {
            kill();
            Game::addPiece(new Queen(color, position));
        }
    }

    return moveSuccessful;
}

set<int> Pawn::getAttackSquares()
{
    set<int> attackSquares = set<int>();
    list<Point> moves = { Point(-1, forwardBy), Point(1, forwardBy) };
    for (Point move : moves) {
        Point point = position + move;
        if (point.inBounds()) {
            attackSquares.insert(point.getInt());
        }
    }
	return attackSquares;
}

list<Point> Pawn::getPossibleMoves()
{
    list<Point> possible = list<Point>();
    bool guardingKing = Game::amIGuardingKing(position);
    bool inCheck = Game::inCheck(color);

    Point point = position;
    point.addY(forwardBy);
    bool oneBlankSpace = (Game::getPieceAt(point) == nullptr);

    // if the square ahead of us is safe and available
    if (oneBlankSpace && jeopardizeKing(point, guardingKing, inCheck) == false) {
        possible.push_back(point);
    }

    // if we are in starting position
    if (position.getY() == firstRank) {
        point = position;
        point.addY(forwardBy * 2);

        bool twoBlankSpaces = oneBlankSpace && Game::getPieceAt(point) == nullptr;

        // if two squares ahead are safe and available
        if (twoBlankSpaces && jeopardizeKing(point, guardingKing, inCheck) == false) {
            possible.push_back(point);
        }
    }

    // attack moves
    Point upLeft = position + Point(-1, forwardBy);
    Piece* upLeftPiece = Game::getPieceAt(upLeft);

    Point upRight = position + Point(1, forwardBy);
    Piece* upRightPiece = Game::getPieceAt(upRight);

    // attack normal, NW direction
    if (upLeftPiece != nullptr && upLeftPiece->getColor() != color && jeopardizeKing(upLeft, guardingKing, inCheck) == false) {
        possible.push_back(upLeft);
    }

    // attack normal, NE direction
    if (upRightPiece != nullptr && upRightPiece->getColor() != color && jeopardizeKing(upRight, guardingKing, inCheck) == false) {
        possible.push_back(upRight);
    }

    // en passant
    if (position.getY() == enPassantRank) {
        Piece* leftPiece = Game::getPieceAt(position + Point(-1, 0));
        Piece* rightPiece = Game::getPieceAt(position + Point(1, 0));

        if (leftPiece != nullptr && leftPiece->getPosition() == potentialEnPassant && 
            jeopardizeKing(upLeft, guardingKing, inCheck) == false) {
            possible.push_back(upLeft);
        }

        if (rightPiece != nullptr && rightPiece->getPosition() == potentialEnPassant &&
            jeopardizeKing(upRight, guardingKing, inCheck) == false) {
            possible.push_back(upRight);
        }
    }
   
    // promotion is handled in the move method

    return possible;
}

void Pawn::draw()
{
}
