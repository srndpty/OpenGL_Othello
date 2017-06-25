#include "Stone.h"


Stone::Stone(Vec2f aPos, Vec2f aSize)
{
	vertex[0] = geom[0] = { -aSize.x / 2, +aSize.y / 2 };
	vertex[1] = geom[1] = { +aSize.x / 2, +aSize.y / 2 };
	vertex[2] = geom[2] = { +aSize.x / 2, -aSize.y / 2 };
	vertex[3] = geom[3] = { -aSize.x / 2, -aSize.y / 2 };
	uv[0] = { 0, 1 };
	uv[1] = { 1, 1 };
	uv[2] = { 1, 0 };
	uv[3] = { 0, 0 };
	pos = aPos;
	size = aSize * 0.5f;
	// ”½‰f
	for (size_t i = 0; i < DEFAULT_VERTS_COUNT; i++)
	{
		geom[i].x = pos.x + vertex[i].x;
		geom[i].y = pos.y + vertex[i].y;
	}
}

Stone::~Stone()
{
}
