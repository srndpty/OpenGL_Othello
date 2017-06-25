// Stone.h
// �I�Z���̐�1��\������N���X

#pragma once

#include "Def.h"
#include "Sprite.h"

class Stone : public Sprite<DEFAULT_VERTS_COUNT>
{
public:
	enum class Type
	{
		Black,
		White,
		None
	};

	// �摜���̕�����
	static constexpr int HORIZONTAL_MAX = 4;
	static constexpr int VERTICAL_MAX = 1;
	static constexpr float SIDE_LENGTH = 0.15f;
	static constexpr Vec2f SIZE = { SIDE_LENGTH, SIDE_LENGTH };
	static constexpr Vec2f BASE_POS = { -0.5f, -0.3f };

public:
	/// special
	Stone(Vec2f aPos, Vec2f aSize);
	~Stone();

	/// normal
	void SetType(const int type); // ��ނ̐ݒ�
};

