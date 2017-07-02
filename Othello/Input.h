// Input.h
// 入力の制御

#pragma once

#include "Vec2.h"

// キーの状態
struct State
{
	bool pressed;
	bool lastPressed;
};

// 入力制御クラス
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
	// 入力状態を1フレーム進める
	void Update()
	{
		// キー
		for (size_t i = 0; i < KEY_MAX; i++)
		{
			mKeyStates[i].lastPressed = mKeyStates[i].pressed;
		}

		// マウス
		for (size_t i = 0; i < MOUSE_MAX; i++)
		{
			mMouseStates[i].lastPressed = mMouseStates[i].pressed;
		}


	}

	// 入力の現在状態をリセット
	void ResetNow()
	{
		// キー
		for (size_t i = 0; i < KEY_MAX; i++)
		{
			mKeyStates[i].pressed = false;
		}

		// マウス
		for (size_t i = 0; i < MOUSE_MAX; i++)
		{
			mMouseStates[i].pressed = false;
		}

	}

	// 指定のキーが押された瞬間かどうかを取得
	bool GetButtomDown(int key)
	{
		return mKeyStates[key].lastPressed == false && mKeyStates[key].pressed == true;
	}
};
