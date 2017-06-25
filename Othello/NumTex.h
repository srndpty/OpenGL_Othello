#pragma once

#include <iostream>

#include "Sprite.h"


template<int VertsCount = 4>
class NumTex : public Sprite<VertsCount>
{
public:
	static constexpr Vec2f DEF_SIZE = Vec2f{ 0.15f, 0.15f };

public:
	NumTex(Vec2f aPos, Vec2f aSize)
	{
		static_assert(VertsCount == 4, "VertsCount == 4");
		vertex[0] = geom[0] = { -aSize.x / 2, +aSize.y / 2 };
		vertex[1] = geom[1] = { +aSize.x / 2, +aSize.y / 2 };
		vertex[2] = geom[2] = { +aSize.x / 2, -aSize.y / 2 };
		vertex[3] = geom[3] = { -aSize.x / 2, -aSize.y / 2 };
		RefreshUv(0);
		pos = aPos;
		size = aSize * 0.5f;
		// ”½‰f
		for (size_t i = 0; i < VertsCount; i++)
		{
			geom[i].x = pos.x + vertex[i].x;
			geom[i].y = pos.y + vertex[i].y;
		}
	}

	~NumTex()
	{
	}

	void Update(int aNum)
	{
		if (aNum < 0 || 10 <= aNum)
		{
			std::cout << "aNum must be one digit but " << aNum << "\n";
			aNum = 0;
		}
		mNum = aNum;
		RefreshUv(aNum);
	}

	void RefreshUv(int index)
	{
		uv[0] = { index / 10.f, 1 };
		uv[1] = { (index + 1) / 10.f, 1 };
		uv[2] = { (index + 1) / 10.f, 0 };
		uv[3] = { index / 10.f, 0 };
	}

private:
	int mNum;
};
