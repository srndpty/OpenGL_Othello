// Vec4.h
// x, y, z, w の4要素を持つクラス

#pragma once

// Vector4
template<typename T>
struct Vec4
{
public:
	// member
	T x, y, z, w;

public:
	/// special member functions
	// default ctor
	Vec4()
		: x(T())
		, y(T())
		, z(T())
		, w(T())
	{
	}

	// ctor
	constexpr Vec4(T a, T b, T c, T d)
		: x(a)
		, y(b)
		, z(c)
		, w(d)
	{
	}

	// dtor
	~Vec4() = default;

	// multiply
	Vec4 operator*(T a)
	{
		return{ x * a, y * a, z * a, w * a };
	}

	// plus
	Vec4 operator+(const Vec4& a)
	{
		return{ x + a.x, y + a.y, z + a.z, w + a.w };
	}

	// plus const
	const Vec4 operator+(const Vec4& a) const
	{
		return{ x + a.x, y + a.y, z + a.z, w + a.w };
	}

	// plus equals
	Vec4& operator+=(Vec4 a)
	{
		x += a.x;
		y += a.y;
		y += a.y;
		z += a.z;
		w += a.w;
		return *this;
	}

	// plus equals const
	const Vec4& operator+=(Vec4 a) const
	{
		x += a.x;
		y += a.y;
		z += a.z;
		w += a.w;
		return *this;
	}
};

// エイリアスアクセスを提供
using Vec4f = Vec4<float>;
using Vec4i = Vec4<int>;
