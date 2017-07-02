// Stone.h
// オセロの石1個を表現するクラス

#pragma once

#include "Def.h"
#include "Sprite.h"

class Stone : public Sprite<DEFAULT_VERTS_COUNT>
{
public:
	// 石の種類
	enum class Type
	{
		Black,
		White,
		None,
		Available,
	};

	// 画像内の分割数
	static constexpr int HORIZONTAL_MAX = 4;
	static constexpr int VERTICAL_MAX = 1;
	static constexpr float SIDE_LENGTH = 0.15f;
	static constexpr Vec2f SIZE = { SIDE_LENGTH, SIDE_LENGTH };

private:
	Type mType; // 種類


public:
	/// special
	Stone();
	Stone(const Vec2f& aPos, const Vec2f& aSize);
	~Stone();

	/// normal
	void SetType(const Type type); // 種類の設定
	Type GetType() const;
	Type GetOpponentType() const;
};

