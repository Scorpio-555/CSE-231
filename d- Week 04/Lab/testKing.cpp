#include "testKing.h"
#include "king.h"
#include "pawn.h"
#include "rook.h"
#include "knight.h"
#include "game.h"
#include "bishop.h"
#include "queen.h"

#include <cassert>
void TestKing::run()
{
	Game::reset();
	testOneSpaceH();		// horizontal, move left and right
	testOneSpaceV();		// vertical, up and down
	testOneSpaceD();		// diagonal, NW, NE, SE, SW
	testTwoSpaceH();		// king should tell us he can't move two spaces
	testTwoSpaceV();
	testTwoSpaceD();
	testAttackH();			// horizontal, attack left and right
	testAttackV();
	testAttackD();
	testAttackComrade();	// king should tell us he can't attack comrade
	testMoveIntoCheck();	// king should tell us he can't move into check
	testMoveOutOfCheck();
	testStillInCheck();		// king should tell us he can't move to a place where he remains in check
	testCastle();			// when you can castle
	testFailedCastle();		// and when you can't
}

void TestKing::testOneSpaceH()
{
	//Test 1 - One Space Horizontal Move

	// SETUP
	Piece* test1King = new King(Color::BLACK, Point(4, 0));
	Game::addPiece(test1King);
	// EXERCISE
	bool moveSuccessful = test1King->move(Point(3, 0)) &&	// left
						  test1King->move(Point(4, 0));		// and right again
	// VERIFY
	assert(moveSuccessful);
	// TEARDOWN
	Game::reset();
}

void TestKing::testOneSpaceV()
{
	//Test 2 - One Space Vertical Move

	// SETUP
	Piece* test2King = new King(Color::WHITE, Point(4, 7));
	Game::addPiece(test2King);
	// EXERCISE
	bool moveSuccessful = test2King->move(Point(4, 6)) &&	// down
						  test2King->move(Point(4, 7));		// back up
	// VERIFY
	assert(moveSuccessful);
	// TEARDOWN
	Game::reset();
}

void TestKing::testOneSpaceD()
{
	//Test 3 - One Space Diagonal Move

	// SETUP
	Piece* test3King = new King(Color::BLACK, Point(4, 0));
	Game::addPiece(test3King);
	// EXERCISE
	bool moveSuccessful = test3King->move(Point(3, 1)) &&	// NW
						  test3King->move(Point(4, 0)) &&	// SE
						  test3King->move(Point(3, 1)) &&	// NE
						  test3King->move(Point(4, 0));		// SW
	// VERIFY
	assert(moveSuccessful);
	// TEARDOWN
	Game::reset();
}

void TestKing::testTwoSpaceH()
{
	//Test 4 - Two Space Horizontal Move

	// SETUP
	Piece* test4King = new King(Color::BLACK, Point(6, 3));
	Game::addPiece(test4King);
	// EXERCISE
	bool moveSuccessful = test4King->move(Point(4, 3));
	// VERIFY
	assert(!moveSuccessful);
	assert(test4King->getPosition() == Point(6, 3));
	// TEARDOWN
	Game::reset();
}

void TestKing::testTwoSpaceV()
{
	//Test 5 - Two Space Vertical Move

	// SETUP
	Piece* test5King = new King(Color::WHITE, Point(5, 3));
	Game::addPiece(test5King);
	// EXERCISE
	bool moveSuccessful = test5King->move(Point(5, 1));
	// VERIFY
	assert(!moveSuccessful);
	assert(test5King->getPosition() == Point(5, 3));
	// TEARDOWN
	Game::reset();
}

void TestKing::testTwoSpaceD()
{
	//Test 6 - Two Space Diagonal Move

	// SETUP
	Piece* test6King = new King(Color::WHITE, Point(3, 6));
	Game::addPiece(test6King);
	// EXERCISE
	bool moveSuccessful = test6King->move(Point(1, 4));
	// VERIFY
	assert(!moveSuccessful);
	assert(test6King->getPosition() == Point(3, 6));
	// TEARDOWN
	Game::reset();
}

void TestKing::testAttackH()
{
	//Test 7 - Horizontal Attack Move

	// SETUP
	Piece* test7King = new King(Color::BLACK, Point(3, 3));
	Piece* test7PawnL = new Pawn(Color::WHITE, Point(2, 3));
	Piece* test7PawnR = new Pawn(Color::WHITE, Point(4, 3));
	Game::addPiece(test7King);
	Game::addPiece(test7PawnL);
	Game::addPiece(test7PawnR);
	// EXERCISE
	bool moveSuccessful = test7King->move(Point(2, 3)) &&	// attack left
						  test7King->move(Point(3, 3)) &&	// back in position
						  test7King->move(Point(4, 3));		// attack right
	// VERIFY
	assert(moveSuccessful);
	assert(test7King->getPosition() == Point(4, 3));
	assert(!test7PawnL->isAlive());
	assert(!test7PawnR->isAlive());
	// TEARDOWN
	Game::reset();
}

void TestKing::testAttackV()
{
	//Test 8 - Vertical Attack Move

	// SETUP
	Piece* test8King = new King(Color::BLACK, Point(5, 3));
	Piece* test8PawnU = new Pawn(Color::WHITE, Point(5, 4));
	Piece* test8PawnD = new Pawn(Color::WHITE, Point(5, 2));
	Game::addPiece(test8King);
	Game::addPiece(test8PawnU);
	Game::addPiece(test8PawnD);
	// EXERCISE
	bool moveSuccessful = test8King->move(Point(5, 4)) &&	// attack up
						  test8King->move(Point(5, 3)) &&	// back in position
						  test8King->move(Point(5, 2));		// attack down
	// VERIFY
	assert(moveSuccessful);
	assert(test8King->getPosition() == Point(5, 2));
	assert(!test8PawnU->isAlive());
	assert(!test8PawnD->isAlive());
	// TEARDOWN
	Game::reset();
}

void TestKing::testAttackD()
{
	//Test 9 - Diagonal Attack Move

	// SETUP
	Piece* test9King = new King(Color::WHITE, Point(5, 4));
	Piece* test9RookSW = new Rook(Color::BLACK, Point(4, 3));
	Piece* test9KnightNW = new Knight(Color::BLACK, Point(4, 5));
	Piece* test9PawnSE = new Pawn(Color::BLACK, Point(5, 2));
	Piece* test9KnightNE = new Knight(Color::BLACK, Point(6, 3));
	Game::addPiece(test9King);
	Game::addPiece(test9RookSW);
	Game::addPiece(test9KnightNW);
	Game::addPiece(test9PawnSE);
	Game::addPiece(test9KnightNE);
	// EXERCISE
	bool moveSuccessful = test9King->move(Point(4, 3)) && // attack down left
						  test9King->move(Point(5, 2)) && // attack down right
						  test9King->move(Point(6, 3)) && // attack up right
						  test9King->move(Point(5, 4)) && // back into position
						  test9King->move(Point(4, 5));   // attack up left
	// VERIFY
	assert(moveSuccessful);
	assert(test9King->getPosition() == Point(4, 5));
	assert(!test9RookSW->isAlive());
	assert(!test9KnightNW->isAlive());
	assert(!test9PawnSE->isAlive());
	assert(!test9KnightNE->isAlive());
	// TEARDOWN
	Game::reset();
}

void TestKing::testAttackComrade()
{
	//Test 10 - Attacking Own Color

	// SETUP
	Piece* test10King = new King(Color::BLACK, Point(3, 3));
	Piece* test10Pawn = new Pawn(Color::BLACK, Point(2, 3));
	Game::addPiece(test10King);
	Game::addPiece(test10Pawn);
	// EXERCISE
	bool moveSuccessful = test10King->move(Point(2, 3));
	// VERIFY
	assert(!moveSuccessful);
	assert(test10King->getPosition() == Point(3, 3));
	assert(test10Pawn->isAlive());
	// TEARDOWN
	Game::reset();
}

void TestKing::testMoveIntoCheck()
{
	//Test 11 - Moving Into Check

	// SETUP
	Piece* test11King = new King(Color::WHITE, Point(4, 7));
	Piece* test11Bishop = new Bishop(Color::BLACK, Point(7, 3));
	Game::addPiece(test11King);
	Game::addPiece(test11Bishop);
	// EXERCISE
	bool moveSuccessful = test11King->move(Point(4, 6));
	// VERIFY
	assert(!moveSuccessful);
	assert(test11King->getPosition() == Point(4, 7));
	// TEARDOWN
	Game::reset();
}

void TestKing::testMoveOutOfCheck()
{
	//Test 12 - Moving Out of Check

	// SETUP
	Piece* test12King = new King(Color::BLACK, Point(6, 7));
	Piece* test12Queen = new Queen(Color::WHITE, Point(6, 2));
	Game::addPiece(test12King);
	Game::addPiece(test12Queen);
	// EXERCISE
	bool moveSuccessful = test12King->move(Point(5, 7));
	// VERIFY
	assert(moveSuccessful);
	assert(test12King->getPosition() == Point(5, 7));
	// TEARDOWN
	Game::reset();
}

void TestKing::testStillInCheck()
{
	//Test 13 - Failure to Move Out of Check

	// SETUP
	Piece* test13King = new King(Color::WHITE, Point(1, 7));
	Piece* test13Rook = new Rook(Color::BLACK, Point(1, 1));
	Piece* test13Knight = new Knight(Color::BLACK, Point(3, 5));
	Game::addPiece(test13King);
	Game::addPiece(test13Rook);
	Game::addPiece(test13Knight);
	// EXERCISE
	bool moveSuccessful = test13King->move(Point(2, 7));
	// VERIFY
	assert(!moveSuccessful);
	assert(test13King->getPosition() == Point(1, 7));
	// TEARDOWN
	Game::reset();
}

void TestKing::testCastle()
{
	//Test 14 - Castling
	testQueensCastle();
	testKingsCastle();
}

void TestKing::testQueensCastle()
{
	//Test 14a - Queen's Castling

	// SETUP
	Piece* test14King = new King(Color::WHITE, Point(4, 0));
	Piece* test14Rook = new Rook(Color::WHITE, Point(0, 0));
	Game::addPiece(test14King);
	Game::addPiece(test14Rook);
	// EXERCISE
	bool moveSuccessful = test14King->move(Point(2, 0));
	// VERIFY
	assert(moveSuccessful);
	assert(test14King->getPosition() == Point(2, 0));
	// TEARDOWN
	Game::reset();
}

void TestKing::testKingsCastle()
{
	//Test 14b - King's Castling

	// SETUP
	Piece* test14King = new King(Color::WHITE, Point(4, 0));
	Piece* test14Rook = new Rook(Color::WHITE, Point(7, 0));
	Game::addPiece(test14King);
	Game::addPiece(test14Rook);
	// EXERCISE
	bool moveSuccessful = test14King->move(Point(6, 0));
	// VERIFY
	assert(moveSuccessful);
	assert(test14King->getPosition() == Point(6, 0));
	// TEARDOWN
	Game::reset();
}

void TestKing::testFailedCastle()
{
	//Test 15 - Failed Castle Attempt

	// SETUP
	Piece* test15KingW = new King(Color::WHITE, Point(4, 0));
	Piece* test15KingB = new King(Color::BLACK, Point(4, 7));
	Piece* test15RookL = new Rook(Color::BLACK, Point(0, 7));
	Piece* test15Queen = new Queen(Color::BLACK, Point(3, 7));
	Piece* test15RookW = new Rook(Color::WHITE, Point(7, 0));
	Piece* test15RookR = new Rook(Color::BLACK, Point(7, 7));
	Game::addPiece(test15KingW);
	Game::addPiece(test15KingB);
	Game::addPiece(test15RookL);
	Game::addPiece(test15Queen);
	Game::addPiece(test15RookW);
	Game::addPiece(test15RookR);
	test15KingW->move(Point(4, 1));
	test15KingW->move(Point(4, 0));
	test15RookR->move(Point(6, 7));
	test15RookR->move(Point(7, 7));
	// EXERCISE
	bool moveSuccessful = test15KingW->move(Point(6, 0)) || 
						  test15KingB->move(Point(2, 7)) || 
						  test15KingB->move(Point(6, 7));
	// VERIFY
	assert(!moveSuccessful);
	assert(test15KingW->getPosition() == Point(4, 0));
	assert(test15KingB->getPosition() == Point(4, 7));
	// TEARDOWN
	Game::reset();
}
