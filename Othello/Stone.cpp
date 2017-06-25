// Stone.cpp
// オセロの石1個分のクラス

#include "Stone.h"


Stone::Stone()
{
}

//----------------------------------------
// ctor
Stone::Stone(Vec2f aPos, Vec2f aSize)
{
	vertex[0] = geom[0] = { -aSize.x / 2, +aSize.y / 2 };
	vertex[1] = geom[1] = { +aSize.x / 2, +aSize.y / 2 };
	vertex[2] = geom[2] = { +aSize.x / 2, -aSize.y / 2 };
	vertex[3] = geom[3] = { -aSize.x / 2, -aSize.y / 2 };
	pos = aPos;
	size = aSize;

	// 仮に黒
	SetType(Type::None);
}

//----------------------------------------
// dtor
Stone::~Stone()
{
}

//----------------------------------------
// 種類の設定
void Stone::SetType(const Type type)
{
	uv[0] = { 1.0f / HORIZONTAL_MAX * (static_cast<int>(type) + 0), 1.0f };
	uv[1] = { 1.0f / HORIZONTAL_MAX * (static_cast<int>(type) + 1), 1.0f };
	uv[2] = { 1.0f / HORIZONTAL_MAX * (static_cast<int>(type) + 1), 0.0f };
	uv[3] = { 1.0f / HORIZONTAL_MAX * (static_cast<int>(type) + 0), 0.0f };
}
