// Shader.h
// �V�F�[�_�[���Ǘ�����

#pragma once

#include "GLFW/glfw3.h"

// �V�F�[�_�[���Ǘ�����N���X
class Shader
{
public:
	// �V�F�[�_�[�̃v���p�e�B��
	static const char* ID_position;
	static const char* ID_uv;
	static const char* ID_texture;
	static const char* ID_MVP;
	static const char* ID_color;

public:
	int mPositionLocation;
	int mUvLocation;
	int mTextureLocation;
	int mMvpLocation;
	int mColorLocation;

private:
	GLuint mProgramId;

public:
	/// special
	Shader();
	~Shader();

	/// normal
	void SetUp();
};

