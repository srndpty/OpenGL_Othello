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
	static constexpr Vec2i TOP_LEFT_POS = { 62, 78 };
	static constexpr Vec2i STONE_SIZE = { 36, 36 };

private:
	Stone mBoard[Game::FIELD_SIZE.y][Game::FIELD_SIZE.x]; // 盤面の状態
	Stone::Type mTurn = Stone::Type::Black;

public:
	/// special
	Game();
	~Game();

	/// normal
	// 描画
	void Draw(const int id);

	// 指定の座標上にあるところに石を置く
	void SetStone(const Vec2i& pos);
	Vec2i GetCurrentScore() const; // 現在の黒と白の数をVec2で取得
	void ResetBoard(); // 初期化
	bool CheckPlayable();
	void SwitchTurn(); // ターンチェンジ

private:
	size_t TryFlip(const Vec2i& index, const Stone::Type type); // 指定の場所に石を置いて何個ひっくり返せるか取得
	void PlaceStone(const Vec2i& index, const Stone::Type type); // 実際に石を置き、反転もさせる
};

