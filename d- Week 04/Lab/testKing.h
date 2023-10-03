#pragma once

class TestKing {
public:
	void run();
private:
	void testOneSpaceH();		// horizontal, move left and right
	void testOneSpaceV();		// vertical, up and down
	void testOneSpaceD();		// diagonal, NW, NE, SE, SW
	void testTwoSpaceH();		// king should tell us he can't move two spaces
	void testTwoSpaceV();
	void testTwoSpaceD();
	void testAttackH();		// horizontal, attack left and right
	void testAttackV();
	void testAttackD();
	void testAttackComrade();	// king should tell us he can't attack comrade
	void testMoveIntoCheck();	// king should tell us he can't move into check
	void testMoveOutOfCheck();
	void testStillInCheck();	// king should tell us he can't move to a place where he remains in check
	void testCastle();        	// when you can castle
	void testQueensCastle();
	void testKingsCastle();   
	void testFailedCastle();	// and when you can't
};
