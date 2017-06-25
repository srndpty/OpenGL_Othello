// Input.h
// ���͂̐���

#pragma once

// �L�[�̏��
struct KeyState
{
	bool pressed;
	bool lastPressed;
};

// ���͐���N���X
class Input
{
public:
	static constexpr int KEY_MAX = 512;

	// ���͏�Ԃ�1�t���[���i�߂�
	void Update()
	{
		for (size_t i = 0; i < KEY_MAX; i++)
		{
			mKeyStates[i].lastPressed = mKeyStates[i].pressed;
		}
	}

	// ���͂̌��ݏ�Ԃ����Z�b�g
	void ResetNow()
	{
		for (size_t i = 0; i < KEY_MAX; i++)
		{
			mKeyStates[i].pressed = false;
		}
	}

	// �w��̃L�[�������ꂽ�u�Ԃ��ǂ������擾
	bool GetButtomDown(int key)
	{
		return mKeyStates[key].lastPressed == false && mKeyStates[key].pressed == true;
	}

public:
	KeyState mKeyStates[KEY_MAX];
};
