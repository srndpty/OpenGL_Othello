// Sprite.h
// �摜1�������Ǘ�����

#pragma once

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
	// �`��
	void Draw(int texId)
	{
		// ���f
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
		// attribute������o�^
		glVertexAttribPointer(shader.mPositionLocation, 2, GL_FLOAT, false, 0, geom);
		glVertexAttribPointer(shader.mUvLocation, 2, GL_FLOAT, false, 0, uv);
		glVertexAttribPointer(shader.mColorLocation, 4, GL_FLOAT, false, 0, (const float*)&color);

		// ���f���̕`��
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
	Vec2f size{}; // �T�C�Y
	Vec2f pos{}; // �I�u�W�F�N�g�̒��S���W
	Vec2f vertex[VERTS_COUNT]{}; // ���S���W�����offset�i�Œ�j
	Vec2f geom[VERTS_COUNT]{}; // ���ۂ̃��[���h���W
	Vec2f uv[VERTS_COUNT]{}; // uv
	Vec4f color[VERTS_COUNT]{}; // tint color

private:
	mat4x4 m, p, mvp; // �v�Z�p�ϐ�
};

