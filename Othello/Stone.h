// Stone.h
// �I�Z���̐�1��\������N���X

#pragma once

#include "Def.h"
#include "Sprite.h"

class Stone : public Sprite<DEFAULT_VERTS_COUNT>
{
public:
	Stone(Vec2f aPos, Vec2f aSize);
	~Stone();
};

