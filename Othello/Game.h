// Game.h
// ゲーム全体を管理するクラス
#pragma once

#include "Vec2.h"
#include "Stone.h"

class Game
{
public:
	static constexpr Vec2f BASE_POS = { -0.5f, +0.3f };
	static constexpr Vec2i FIELD_SIZE = { 8, 8 };

private:
	Stone mBoard[Game::FIELD_SIZE.y][Game::FIELD_SIZE.x]; // 盤面の状態

public:
	/// special
	Game();
	~Game();

	/// normal
	void Draw(int id);
};

