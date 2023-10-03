#include "testGame.h"
#include "game.h"
#include "pawn.h"
#include "king.h"
#include <cassert>
#include <set>

void TestGame::run()
{
	testReset();
	testAddPiece();
	testNewGame();
	testGetPieceAt();
	toggleTurnHolder();
	amIGuardingKing();
	testGetEnemyAttackSquares();
	testGetCheckingPath();
	testMovePiece();
	testIsCheckMate();
	testInCheck();
	testRemoveZombies();
}

void TestGame::testReset()
{
	// SETUP
	// EXERCISE
	Game::reset();
	// VERIFY
	assert(Game::pieces.size() == 0);
	assert(Game::currentTurnHolder == Color::WHITE);
	assert(Game::kingInCheck == nullptr);
	assert(Game::checkingPieces.size() == 0);
	assert(Game::checkingPath.size() == 0);
}	// TEARDOWN

void TestGame::testAddPiece()
{
	// SETUP
	Piece* pawn = new Pawn(Color::WHITE, Point(0, 1));
	// EXERCISE
	Game::addPiece(pawn);
	pawn->move(Point(0, 2));
	// VERIFY
	assert(Game::pieces.size() == 1);
	for (Piece * piece : Game::pieces) {
		assert(piece->getName() == Name::PAWN);
		assert(piece->getPosition() == Point(0, 2));
		assert(piece->isAlive());
		assert(piece->getColor() == Color::WHITE);
	}
	// TEARDOWN
	delete[] pawn;
	Game::reset();
}

void TestGame::testNewGame()
{
	// SETUP
	// EXERCISE
	Game::newGame();
	// VERIFY
	assert(Game::pieces.size() == 32);
	for (Piece * piece : Game::pieces) {
		cout << "Test New Game Position " << piece->getPosition().getInt() << endl;

		assert(piece->isAlive());
		if (piece->getColor() == Color::WHITE) {
			assert(piece->getPosition().getInt() >= 0 && piece->getPosition().getInt() < 16);
		}
		else {
			assert(piece->getColor() == Color::BLACK);
			assert(piece->getPosition().getInt() > 47 && piece->getPosition().getInt() < 64);
		}
	}
	assert(Game::currentTurnHolder == Color::WHITE);
	assert(Game::kingInCheck == nullptr);
	assert(Game::checkingPieces.size() == 0);
	assert(Game::checkingPath.size() == 0);
	// TEARDOWN
	for (Piece * piece : Game::pieces) {
		delete[] piece;
	}
	Game::reset();
}

void TestGame::testGetPieceAt()
{
	// SETUP
	Piece* pawn = new Pawn(Color::WHITE, Point(0, 1));
	Game::addPiece(pawn);
	// EXERCISE
	Piece* piece = Game::getPieceAt(Point(0, 1));
	// VERIFY
	assert(pawn->getColor() == piece->getColor());
	assert(pawn->getName() == piece->getName());
	assert(pawn->getPosition() == piece->getPosition());
	assert(pawn->isAlive() == piece->isAlive());
	// TEARDOWN
	delete[] pawn;
	Game::reset();
}

void TestGame::toggleTurnHolder()
{
	// SETUP
	Game::currentTurnHolder = Color::WHITE;
	Piece* king = new King(Color:: WHITE, Point(4, 0));
	Game::kingInCheck = king;
	Piece* pawn = new Pawn(Color::BLACK, Point(3, 1));
	Game::checkingPieces.push_back(pawn);
	Game::checkingPath.push_back(pawn->getPosition());
	Game::pieces.push_back(king);
	Game::pieces.push_back(pawn);
	// EXERCISE
	Game::toggleTurnHolder();
	Color black = Game::currentTurnHolder;
	Game::toggleTurnHolder();
	Color white = Game::currentTurnHolder;
	// VERIFY
	assert(black == Color::BLACK);
	assert(white == Color::WHITE);
	assert(Game::pieces.size() == 2);
	assert(Game::kingInCheck == nullptr);		// ---|
	assert(Game::checkingPath.size() == 0);		//    |---- these should be reset by toggleTurnHolder
	assert(Game::checkingPieces.size() == 0);	// ---|
	// TEARDOWN
	delete[] king;
	delete[] pawn;
	Game::reset();
}

void TestGame::amIGuardingKing()
{
	// SETUP
	Piece* king = new King(Color::WHITE, Point(4, 1));
	Piece* pawn = new Pawn(Color::WHITE, Point(3, 1));
	Piece* rook = new Rook(Color::BLACK, Point(0, 1));
	Game::addPiece(king);
	Game::addPiece(pawn);
	Game::addPiece(rook);
	// EXERCISE
	bool testPassed = Game::amIGuardingKing(Point(3, 1));
	// VERIFY
	assert(testPassed);
	// TEARDOWN
	delete[] king;
	delete[] pawn;
	delete[] rook;
	Game::reset();
}

void TestGame::testGetEnemyAttackSquares()
{
	// SETUP
	Piece* king = new King(Color::WHITE, Point(0, 1));
	Piece* rook = new Rook(Color::BLACK, Point(0, 0));
	Game::addPiece(king);
	Game::addPiece(rook);
	set<int> positions;
	list<Point> squares;
	// EXERCISE
	squares = Game::getEnemyAttackSquares(Color::WHITE); // <--|-- a piece asks the game class for enemy squares. 
	for (Point p : squares) {							 //    |   The piece tells the game what its color is,
		positions.insert(p.getInt());					 //    |-- and game returns squares for the opposite color
	}
	// VERIFY
	assert(positions.size() == 8);
	assert(positions.find(1) != positions.end());
	assert(positions.find(2) != positions.end());
	assert(positions.find(3) != positions.end());
	assert(positions.find(4) != positions.end());
	assert(positions.find(5) != positions.end());
	assert(positions.find(6) != positions.end());
	assert(positions.find(7) != positions.end());
	assert(positions.find(16) != positions.end()); // rook needs to let king know that he can't move to Point(0, 2)
	// TEARDOWN
	delete[] king;
	delete[] rook;
	Game::reset();
}

void TestGame::testGetCheckingPath()
{
	// SETUP
	Piece* king = new King(Color::WHITE, Point(4, 0));
	Piece* rook = new Rook(Color::BLACK, Point(4, 3));
	Game::addPiece(king);
	Game::addPiece(rook);
	Game::currentTurnHolder = Color::WHITE;
	Game::determineCheck();	// sets variables such as checkingPath, checkingPieces, and kingInCheck
	set<int> positions;
	list<Point> squares;
	// EXERCISE
	squares = Game::getCheckingPath();
	for (Point p : squares) {
		positions.insert(p.getInt());
	}
	// VERIFY
	assert(squares.size() == 3);
	assert(positions.find(12) != positions.end()); 
	assert(positions.find(20) != positions.end());
	assert(positions.find(28) != positions.end());
	// TEARDOWN
	delete[] king;
	delete[] rook;
	Game::reset();
}

void TestGame::testMovePiece()
{
	// SETUP
	Piece* pawn = new Pawn(Color::WHITE, Point(0, 1));
	Piece* rook = new Rook(Color::BLACK, Point(0, 7));
	Game::addPiece(pawn);
	Game::addPiece(rook);
	Game::currentTurnHolder = Color::WHITE;
	// EXERCISE
	bool rookMoved = Game::movePiece(rook->getPosition(), Point(0, 6));
	bool pawnMoved = Game::movePiece(pawn->getPosition(), Point(0, 2));
	// VERIFY
	assert(!rookMoved);
	assert(rook->getPosition() == Point(0, 7));
	assert(pawnMoved);
	assert(pawn->getPosition() == Point(0, 2));
	// TEARDOWN
	delete[] pawn;
	delete[] rook;
	Game::reset();
}

void TestGame::testIsCheckMate()
{
	// SETUP
	Piece* king = new King(Color::WHITE, Point(4, 0));
	Piece* rook0 = new Rook(Color::BLACK, Point(0, 0));
	Piece* rook1 = new Rook(Color::BLACK, Point(0, 2));
	Game::addPiece(king);
	Game::addPiece(rook0);
	Game::addPiece(rook1);
	Game::currentTurnHolder = Color::WHITE;
	bool notCheckMatePassed;
	bool isCheckMatePassed;
	// EXERCISE
	notCheckMatePassed = (Game::isCheckMate() == false);
	Game::currentTurnHolder = Color::BLACK;
	Game::movePiece(rook1->getPosition(), Point(0, 1));
	Game::currentTurnHolder = Color::WHITE;
	isCheckMatePassed = (Game::isCheckMate() == true);
	// VERIFY
	assert(notCheckMatePassed);
	assert(isCheckMatePassed);
	// TEARDOWN
}

void TestGame::testInCheck()
{
	// SETUP
	Piece* kingW = new King(Color::WHITE, Point(4, 0));
	Piece* kingB = new King(Color::BLACK, Point(4, 7));
	Piece* rook = new Rook(Color::BLACK, Point(0, 0));
	Game::addPiece(kingW);
	Game::addPiece(kingB);
	Game::addPiece(rook);
	Game::determineCheck();
	// EXERCISE
	bool blackNotInCheck = (Game::inCheck(Color::BLACK) == false);
	bool whiteInCheck = (Game::inCheck(Color::WHITE) == true);
	// VERIFY
	assert(blackNotInCheck);
	assert(whiteInCheck);
	// TEARDOWN
	delete[] kingW;
	delete[] kingB;
	delete[] rook;
	Game::reset();
}

void TestGame::testRemoveZombies()
{
	// SETUP
	Piece* pawn0 = new Pawn(Color::WHITE, Point(0, 1));
	Piece* pawn1 = new Pawn(Color::WHITE, Point(1, 1));
	Game::addPiece(pawn0);
	Game::addPiece(pawn1);
	pawn0->kill();
	// EXERCISE
	Game::removeZombies();
	// VERIFY
	assert(Game::pieces.size() == 1);
	assert(Game::getPieceAt(Point(0, 1)) == nullptr);
	assert(Game::getPieceAt(Point(1, 1))->isAlive());
	// TEARDOWN
	delete[] pawn0;
	delete[] pawn1;
	Game::reset();
}