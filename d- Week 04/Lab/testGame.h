#pragma once
class TestGame {
public:
	void run();
private:
	void testReset();
	void testAddPiece();
	void testNewGame();
	void testGetPieceAt();
	void toggleTurnHolder();
	void amIGuardingKing();
	void testGetEnemyAttackSquares();
	void testGetCheckingPath();
	void testMovePiece();
	void testIsCheckMate();
	void testInCheck();
	void testRemoveZombies();
};
