// Input.h
// ���͂̐���

#pragma once

#include "Vec2.h"

// �L�[�̏��
struct State
{
	bool pressed;
	bool lastPressed;
};

// ���͐���N���X
class Input
{
public:
	static constexpr int KEY_MAX = 512;
	static constexpr int MOUSE_MAX = 16;

public:
	State mKeyStates[KEY_MAX];
	State mMouseStates[MOUSE_MAX];
	Vec2i mCursorPos;

public:
	// ���͏�Ԃ�1�t���[���i�߂�
	void Update()
	{
		// �L�[
		for (size_t i = 0; i < KEY_MAX; i++)
		{
			mKeyStates[i].lastPressed = mKeyStates[i].pressed;
		}

		// �}�E�X
		for (size_t i = 0; i < MOUSE_MAX; i++)
		{
			mMouseStates[i].lastPressed = mMouseStates[i].pressed;
		}


	}

	// ���͂̌��ݏ�Ԃ����Z�b�g
	void ResetNow()
	{
		// �L�[
		for (size_t i = 0; i < KEY_MAX; i++)
		{
			mKeyStates[i].pressed = false;
		}

		// �}�E�X
		for (size_t i = 0; i < MOUSE_MAX; i++)
		{
			mMouseStates[i].pressed = false;
		}

	}

	// �w��̃L�[�������ꂽ�u�Ԃ��ǂ������擾
	bool GetButtomDown(int key)
	{
		return mKeyStates[key].lastPressed == false && mKeyStates[key].pressed == true;
	}
};
