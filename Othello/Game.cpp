#include "Game.h"



Game::Game()
{
	// init field
	for (size_t i = 0; i < FIELD_SIZE.y; i++)
	{
		for (size_t j = 0; j < FIELD_SIZE.x; j++)
		{
			mBoard[i][j] = Stone(BASE_POS + Vec2f(Stone::SIZE.x / 2 * j, -Stone::SIZE.y / 2 * i), Stone::SIZE);
		}
	}

	// Å‰‚ÌˆÊ’u
	mBoard[3][3].SetType(Stone::Type::White);
	mBoard[3][4].SetType(Stone::Type::Black);
	mBoard[4][3].SetType(Stone::Type::Black);
	mBoard[4][4].SetType(Stone::Type::White);
}


Game::~Game()
{
}

void Game::Draw(int id)
{
	for (size_t i = 0; i < Game::FIELD_SIZE.y; i++)
	{
		for (size_t j = 0; j < Game::FIELD_SIZE.x; j++)
		{
			mBoard[i][j].Draw(id);
		}
	}

}
