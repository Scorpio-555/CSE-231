#include "game.h"
#include "pawn.h"
#include "king.h"
#include "rook.h"
#include "knight.h"
#include "bishop.h"
#include "queen.h"

list<Piece*> Game::pieces = list<Piece*>();
Color Game::currentTurnHolder = Color::WHITE;
Piece* Game::kingInCheck = nullptr;
list<Piece*> Game::checkingPieces = list<Piece*>();
set<int> Game::checkingPath = set<int>();
bool Game::checkmate = false;
bool Game::stalemate = false;

Piece* Game::getPieceAt(Point point)
{
	for (Piece* piece : pieces) {
		if (piece->getPosition() == point && piece->isAlive()) {
			return piece;
		}
	}
	return nullptr;
}

Piece* Game::getKing(Color color)
{
	for (Piece* piece : pieces) {
		if (piece->getName() == Name::KING && piece->getColor() == color) {
			return piece;
		}
	}
	return nullptr;
}

set<int> Game::getEnemyAttackSquares(Color yourColor)
{
	set<int> attackSquares = set<int>();

	for (Piece* piece : pieces) {
		if (piece->isAlive() && piece->getColor() != yourColor) {
			for (int square : piece->getAttackSquares())
				attackSquares.insert(square);
		}
	}

	return attackSquares;
}

void Game::addPiece(Piece* piece)
{
	if (getPieceAt(piece->getPosition()) == nullptr) {
		pieces.push_back(piece);
	}
}

void Game::toggleTurnHolder()
{
	if (currentTurnHolder == Color::WHITE) {
		currentTurnHolder = Color::BLACK;
	}
	else {
		currentTurnHolder = Color::WHITE;
	}
	kingInCheck = nullptr;
	checkingPath = set<int>();
	checkingPieces = list<Piece*>();
}

bool Game::amIGuardingKing(Point piecePoint)
{
	// first, let's determine if we can draw a straight line from the piece to its king
	Piece* piece = getPieceAt(piecePoint);
	Piece* king = getKing(piece->getColor());
	Point kingPoint = king->getPosition();
	Point enemyDirection = getDirection(kingPoint, piecePoint);

	if (enemyDirection == Point()) {	// piece and king are not lined up
		return false;
	}
	else {
		// now we know we can draw straight line from peice to king, check if there's only empty squares btwn the two
		Point point = kingPoint + enemyDirection;
		while (point != piecePoint) {
			// if we bumped into someone other than the piece in question, the piece in question isn't guarding!
			if (Game::getPieceAt(point) != nullptr) {
				return false;
			}

			point = point + enemyDirection;
		}

		// now that we know there's only empty squares btwn piece & king, check if piece is btwn king & bad guy
		bool done = false;
		point = piecePoint + enemyDirection;
		Piece* potentialBadGuy = nullptr;
		while (!done) {
			potentialBadGuy = getPieceAt(point);
			if (point.inBounds() == false) {					// hit the edge of board
				done = true;
			}
			else if (potentialBadGuy != nullptr) {				// came across a game piece
				done = true;
			}
			else {												// found an empty game square
				point = point + enemyDirection;
			}
		}

		// we found a game piece
		if (potentialBadGuy != nullptr) {
			// we found an enemy
			if (potentialBadGuy->getColor() != piece->getColor()) {
				// dealing with N,S,E,W
				if (enemyDirection.getX() == 0 || enemyDirection.getY() == 0) {
					// we got him!
					if (potentialBadGuy->getName() == Name::QUEEN || potentialBadGuy->getName() == Name::ROOK) {
						return true;
					}
					// wrong piece type
					else {
						return false;
					}
				}
				// dealing with NE,SE,NW,SW
				else {
					// we got him!
					if (potentialBadGuy->getName() == Name::QUEEN || potentialBadGuy->getName() == Name::BISHOP) {
						return true;
					}
					// wrong piece type
					else {
						return false;
					}
				}
			}
			// we found a comrade
			else {
				return false;
			}
		}
		// we didn't find any game piece
		else {
			return false;
		}
	}
}

Point Game::getDirection(Point startingPoint, Point secondPoint) {
	bool sameColumn = startingPoint.getX() == secondPoint.getX();
	bool sameRow = startingPoint.getY() == secondPoint.getY();
	int deltaY = secondPoint.getY() - startingPoint.getY();
	int deltaX = secondPoint.getX() - startingPoint.getX();
	bool sameDiagonal = (abs(deltaY) == abs(deltaX));

	if (sameColumn == false && sameRow == false && sameDiagonal == false) {
		return Point();
	}
	else {
		int x = 0;
		if (deltaX != 0) {
			x = deltaX / abs(deltaX);	// normalize so that the magnitude of x is 1
		}

		int y = 0;
		if (deltaY != 0) {
			y = deltaY / abs(deltaY);	// normalize so that the magnitude of y is 1
		}

		return Point(x, y);
	}
}

bool Game::movePiece(Point from, Point to)
{
	Piece* piece = getPieceAt(from);

	if (piece->getColor() != currentTurnHolder) {
		return false;
	}

	if (piece->getName() != Name::PAWN) {
		Pawn::resetPotentialEnPassant();
	}

	return piece->move(to);
}

void Game::draw(int hoverPos, int selectPos)
{
	ogstream gout;

	// draw the checkerboard
	gout.drawBoard();

	// draw any selections
	gout.drawHover(hoverPos);
	gout.drawSelected(selectPos);

	// draw the possible moves
	Piece* piece = getPieceAt(Point(selectPos));
	if (piece != nullptr) {
		for (Point point : piece->getPossibleMoves()) {
			gout.drawPossible(point.getInt());
		}
	}

	// draw the pieces
	for (Piece* p : pieces) {
		if (p->isAlive()) {
			p->draw();
		}
	}
}

bool Game::isEndGame()
{
	determineCheck();

	list<Piece*> currentTeam = list<Piece*>();

	for (Piece* piece : pieces) {
		if (piece->getColor() == currentTurnHolder) {
			currentTeam.push_back(piece);
		}
	}

	// with just two kings, it's stalemate
	if (pieces.size() == 2) {
		stalemate = true;
		return true;
	}

	// if the current turn holder can make a move, game on!
	for (Piece* piece : currentTeam) {
		if (piece->getPossibleMoves().size() > 0) {
			return false;
		}
	}

	// if we have made it to this point, it means we are out of moves. Game Over.
	if (kingInCheck != nullptr) {
		checkmate = true;
	}
	else {
		stalemate = true;
	}

	return true;
}

bool Game::inCheck(Color yourColor)
{
	if (kingInCheck == nullptr) {
		return false;
	}
	else {
		return kingInCheck->getColor() == yourColor;
	}
}

void Game::removeZombies()
{
	list<Piece*> newList = list<Piece*>();

	while (pieces.size() > 0) {
		Piece* piece = pieces.front();
		pieces.pop_front();
		if (piece->isAlive()) {
			newList.push_back(piece);
		}
		else {
			delete[] piece;
		}
	}

	pieces = newList;
}

void Game::reset()
{
	for (Piece* piece : pieces) {
		delete[] piece;
	}
	pieces = list<Piece*>();
	currentTurnHolder = Color::WHITE;
	kingInCheck = nullptr;
	checkingPieces = list<Piece*>();
	checkingPath = set<int>();
	checkmate = false;
	stalemate = false;
}

void Game::newGame()
{
	reset();

	// add white pawns
	for (int i = 8; i < 16; i++) {
		addPiece(new Pawn(Color::WHITE, Point(i)));
	}

	// add black pawns
	for (int i = 48; i < 56; i++) {
		addPiece(new Pawn(Color::BLACK, Point(i)));
	}

	// Rooks
	addPiece(new Rook(Color::WHITE, Point(0, 0)));
	addPiece(new Rook(Color::WHITE, Point(7, 0))); 
	addPiece(new Rook(Color::BLACK, Point(0, 7)));
	addPiece(new Rook(Color::BLACK, Point(7, 7)));

	// Knights
	addPiece(new Knight(Color::WHITE, Point(1, 0)));
	addPiece(new Knight(Color::WHITE, Point(6, 0)));
	addPiece(new Knight(Color::BLACK, Point(1, 7)));
	addPiece(new Knight(Color::BLACK, Point(6, 7)));

	// Bishops
	addPiece(new Bishop(Color::WHITE, Point(2, 0)));
	addPiece(new Bishop(Color::WHITE, Point(5, 0)));
	addPiece(new Bishop(Color::BLACK, Point(2, 7)));
	addPiece(new Bishop(Color::BLACK, Point(5, 7)));

	// Queens 
	addPiece(new Queen(Color::WHITE, Point(3, 0)));
	addPiece(new Queen(Color::BLACK, Point(3, 7)));

	// King
	addPiece(new King(Color::WHITE, Point(4, 0)));
	addPiece(new King(Color::BLACK, Point(4, 7)));
}

void Game::determineCheck()
{
	Piece* king = getKing(currentTurnHolder);
	for (Piece* piece : pieces) {
		if (piece->getColor() != currentTurnHolder) {
			set<int> attackSquares = piece->getAttackSquares();
			if (attackSquares.find(king->getPosition().getInt()) != attackSquares.end()) {
				kingInCheck = king;
				checkingPieces.push_back(piece);
			}
		}
	}

	if (checkingPieces.size() == 1) {
		Piece* piece = checkingPieces.front();
		Point direction = getDirection(piece->getPosition(), kingInCheck->getPosition());
		Point point = piece->getPosition() + direction;
		checkingPath.insert(piece->getPosition().getInt());

		if (direction != Point()) {
			while (point != kingInCheck->getPosition())
			{
				checkingPath.insert(point.getInt());
				point = point + direction;
			}
		}
	}

}
