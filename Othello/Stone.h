// Stone.h
// オセロの石1個を表現するクラス

#pragma once

#include "Def.h"
#include "Sprite.h"

class Stone : public Sprite<DEFAULT_VERTS_COUNT>
{
public:
	Stone(Vec2f aPos, Vec2f aSize);
	~Stone();
};

