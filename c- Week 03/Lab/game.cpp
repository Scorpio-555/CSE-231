#include "game.h"

Piece* Game::getPieceAt(Point point)
{
	return nullptr;
}

list<Point> Game::getEnemyAttackSquares(Color yourColor)
{
	return list<Point>();
}

void Game::addPiece(Piece* piece)
{
}

void Game::toggleTurnHolder()
{
}

bool Game::amIGuardingKing(Point point)
{
	return false;
}

bool Game::movePiece(Point from, Point to)
{
	return false;
}

void Game::draw(Point hoverPos, Point selectPos)
{
}

bool Game::isCheckMate()
{
	return false;
}

bool Game::inCheck(Color yourColor)
{
	return false;
}

void Game::removeZombies()
{
}

void Game::determineCheck()
{
}
