// Vec2.h
// x, yの2要素を持つクラス

#pragma once

// Vector2
template<typename T>
struct Vec2
{
public:
	// member
	T x, y;

public:
	/// special member functions
	// default ctor
	Vec2()
		: x(T())
		, y(T())
	{
	}

	// ctor
	constexpr Vec2(T a, T b)
		: x(a)
		, y(b)
	{
	}

	// dtor
	~Vec2() = default;



	// multiply
	Vec2 operator*(T a)
	{
		return{ x * a, y * a };
	}

	Vec2 operator*(const Vec2& a)
	{
		return{ x * a.x, y * a.y };
	}

	// plus
	Vec2 operator+(const Vec2& a)
	{
		return{ x + a.x, y + a.y };
	}

	// plus const
	const Vec2 operator+(const Vec2& a) const
	{
		return { x + a.x, y + a.y };
	}

	// plus equals
	Vec2& operator+=(Vec2 a)
	{
		x += a.x;
		y += a.y;
		return *this;
	}

	// plus equals const
	const Vec2& operator+=(Vec2 a) const
	{
		x += a.x;
		y += a.y;
		return *this;
	}
};

// エイリアスアクセスを提供
using Vec2f = Vec2<float>;
using Vec2i = Vec2<int>;
