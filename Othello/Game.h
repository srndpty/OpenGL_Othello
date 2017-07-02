// Game.h
// �Q�[���S�̂��Ǘ�����N���X
#pragma once

#include "Vec2.h"
#include "Stone.h"

#include <memory>

class Game
{
public:
	static constexpr Vec2f BASE_POS = { -0.55f, +0.4f };
	static constexpr Vec2i FIELD_SIZE = { 8, 8 };
	static constexpr Vec2i TOP_LEFT_POS = { 32, 24 };
	static constexpr Vec2i STONE_SIZE = { 48, 48 };

private:
	Stone mBoard[Game::FIELD_SIZE.y][Game::FIELD_SIZE.x]; // �Ֆʂ̏��
	Stone::Type mTurn = Stone::Type::Black;
	std::unique_ptr<Stone> mNext = std::make_unique<Stone>(Vec2f{ 0.4f, 0.0f }, Vec2f{ 0.2f, 0.2f });

public:
	/// special
	Game();
	~Game();

	/// normal
	// �`��
	void Draw(const int id);

	// �w��̍��W��ɂ���Ƃ���ɐ΂�u��
	void SetStone(const Vec2i& pos);
	Vec2i GetCurrentScore() const; // ���݂̍��Ɣ��̐���Vec2�Ŏ擾
	void ResetBoard(); // ������
	bool CheckPlayable();
	void SwitchTurn(); // �^�[���`�F���W

private:
	size_t TryFlip(const Vec2i& index, const Stone::Type type); // �w��̏ꏊ�ɐ΂�u���ĉ��Ђ�����Ԃ��邩�擾
	void PlaceStone(const Vec2i& index, const Stone::Type type); // ���ۂɐ΂�u���A���]��������
	bool IsSpaceStone(Stone::Type type) const;
};

