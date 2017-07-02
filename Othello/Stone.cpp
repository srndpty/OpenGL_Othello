// Stone.cpp
// �I�Z���̐�1���̃N���X

#include "Stone.h"


Stone::Stone()
{
}

//----------------------------------------
// ctor
Stone::Stone(const Vec2f& aPos, const Vec2f& aSize)
	: Sprite(aPos, aSize)
{
	// ���ɍ�
	SetType(Type::None);
}

//----------------------------------------
// dtor
Stone::~Stone()
{
}

//----------------------------------------
// ��ނ̐ݒ�
void Stone::SetType(const Type type)
{
	uv[0] = { 1.0f / HORIZONTAL_MAX * (static_cast<int>(type) + 0), 1.0f };
	uv[1] = { 1.0f / HORIZONTAL_MAX * (static_cast<int>(type) + 1), 1.0f };
	uv[2] = { 1.0f / HORIZONTAL_MAX * (static_cast<int>(type) + 1), 0.0f };
	uv[3] = { 1.0f / HORIZONTAL_MAX * (static_cast<int>(type) + 0), 0.0f };
	mType = type;
}

Stone::Type Stone::GetType() const
{
	return mType;
}

Stone::Type Stone::GetOpponentType() const
{
	switch (mType)
	{
	case Stone::Type::Black:
		return Stone::Type::White;
	case Stone::Type::White:
		return Stone::Type::Black;
	case Stone::Type::None:
	default:
		return Stone::Type::None;
	}
}
