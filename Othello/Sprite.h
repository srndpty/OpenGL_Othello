// Sprite.h
// 画像1枚分を管理する

#pragma once

#include <iostream>

#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include "Vec2.h"
#include "Vec4.h"
#include "linmath.h"
#include "Def.h"
#include "Shader.h"

extern Shader shader;

// base class for sprite object
template<int VERTS_COUNT>
class Sprite
{
public:
	/// special
	// default ctor
	Sprite()
	{
		//std::cout << "default constructor of Sprite called. this shouldn't be happened!\n";
		//SHOULD_NOT_REACH_HERE();
	}

	Sprite(const Vec2f& aPos, const Vec2f& aSize)
		: pos(aPos)
		, size(aSize)
	{
		vertex[0] = geom[0] = { -aSize.x / 2, +aSize.y / 2 };
		vertex[1] = geom[1] = { +aSize.x / 2, +aSize.y / 2 };
		vertex[2] = geom[2] = { +aSize.x / 2, -aSize.y / 2 };
		vertex[3] = geom[3] = { -aSize.x / 2, -aSize.y / 2 };

		SetColor({ 1.0f, 1.0f, 1.0f, 1.0f });
	}

	// ctor init color
	Sprite(const vec4& v)
	{
		SetColor(v);
	}

	// dtor
	virtual ~Sprite() = default;

	/// normal
	// 描画
	// NOTE: linmath.h がnon-constなvec4[]などを要求するので、この関数自体をconstにできない
	void Draw(int texId)
	{
		// 反映
		for (size_t i = 0; i < VERTS_COUNT; i++)
		{
			geom[i] = pos + vertex[i];
		}

		mat4x4_identity(m);
		mat4x4_translate_in_place(m, pos.x, pos.y, 0);
		mat4x4_ortho(p, -ASPECT_RATIO, ASPECT_RATIO, -1.f, 1.f, 1.f, -1.f);
		mat4x4_mul(mvp, p, m);

		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glUniformMatrix4fv(shader.mMvpLocation, 1, false, (const GLfloat*)mvp);
		// attribute属性を登録
		glVertexAttribPointer(shader.mPositionLocation, 2, GL_FLOAT, false, 0, geom);
		glVertexAttribPointer(shader.mUvLocation, 2, GL_FLOAT, false, 0, uv);
		glVertexAttribPointer(shader.mColorLocation, 4, GL_FLOAT, false, 0, (const float*)&color);

		// モデルの描画
		glBindTexture(GL_TEXTURE_2D, texId);
		glDrawArrays(GL_TRIANGLE_FAN, 0, VERTS_COUNT);
	}

	void SetColor(Vec4f col)
	{
		for (size_t i = 0; i < VERTS_COUNT; i++)
		{
			color[i] = col;
		}
	}

public:
	Vec2f size{}; // サイズ
	Vec2f pos{}; // オブジェクトの中心座標
	Vec2f vertex[VERTS_COUNT]{}; // 中心座標からのoffset（固定）
	Vec2f geom[VERTS_COUNT]{}; // 実際のワールド座標
	Vec2f uv[VERTS_COUNT]{}; // uv
	Vec4f color[VERTS_COUNT]{}; // tint color

private:
	mat4x4 m, p, mvp; // 計算用変数
};

