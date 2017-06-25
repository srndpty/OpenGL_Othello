// Input.h
// 入力の制御

#pragma once

// キーの状態
struct KeyState
{
	bool pressed;
	bool lastPressed;
};

// 入力制御クラス
class Input
{
public:
	static constexpr int KEY_MAX = 512;

	// 入力状態を1フレーム進める
	void Update()
	{
		for (size_t i = 0; i < KEY_MAX; i++)
		{
			mKeyStates[i].lastPressed = mKeyStates[i].pressed;
		}
	}

	// 入力の現在状態をリセット
	void ResetNow()
	{
		for (size_t i = 0; i < KEY_MAX; i++)
		{
			mKeyStates[i].pressed = false;
		}
	}

	// 指定のキーが押された瞬間かどうかを取得
	bool GetButtomDown(int key)
	{
		return mKeyStates[key].lastPressed == false && mKeyStates[key].pressed == true;
	}

public:
	KeyState mKeyStates[KEY_MAX];
};
