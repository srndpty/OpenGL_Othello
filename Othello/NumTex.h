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
		: Sprite(aPos, aSize)
	{
		static_assert(VertsCount == 4, "VertsCount == 4");
		RefreshUv(0);
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
