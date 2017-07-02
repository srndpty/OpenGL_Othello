// ”CˆÓ‚ÌŒ…”‚Ì”’l‚ğ•`‰æ‚·‚éƒNƒ‰ƒX
#pragma once

#include <memory>

#include "NumTex.h"
#include "Vec2.h"
#include "Util.h"

template<int DIGITS = 1>
class NumDisp
{
public:
	enum class Alignment
	{
		Left,
		Center,
		Right,
	};

private:
	std::unique_ptr<NumTex<>> mTex[DIGITS];
	uint32_t mNum = 0;

public:
	/// special
	NumDisp(const Vec2f& aPos)
	{
		Initialize(aPos, NumTex<>::DEF_SIZE);
	}

	NumDisp(const Vec2f& aPos, const Vec2f& aSize)
	{
		Initialize(aPos, aSize);
	}

	~NumDisp()
	{
	}

	/// normal
	void Initialize(const Vec2f& aPos, const Vec2f& aSize)
	{
		for (uint32_t i = 0; i < DIGITS; i++)
		{
			mTex[i] = std::make_unique<NumTex<>>(Vec2f{ aPos.x - i * aSize.x / 2, aPos.y }, aSize);
		}
	}

	void Update(int aNum)
	{
		mNum = aNum;
		for (uint32_t i = 0; i < DIGITS; i++)
		{
			mTex[i]->Update(aNum / Pow10(i) % 10);
		}
	}

	void Draw(int id)
	{
		for (uint32_t i = 0; i < DIGITS; i++)
		{
			if (i == 0 || mNum >= Pow10(i))
			{
				mTex[i]->Draw(id);
			}
		}
	}


};




