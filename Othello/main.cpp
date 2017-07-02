#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <numeric>
#include <memory>
#include "linmath.h"

#include "Shader.h"
#include "Vec2.h"
#include "Def.h"
#include "Input.h"
#include "Sprite.h"
#include "Loader.h"
#include "Random.h"
#include "NumDisp.h"
#include "Stone.h"
#include "Game.h"

#pragma comment(lib, "opengl32.lib")

Input input;
Shader shader;
Random random;

namespace
{
	enum class GameState
	{
		Init,
		Main,
		Gameover
	};

	const char* GAME_TITLE = "Reversi Game";

	// window
	GLFWwindow* window = nullptr;

	// main game
	GameState gameState = GameState::Init;
	std::unique_ptr<Game> game;
	std::unique_ptr<Stone> board[Game::FIELD_SIZE.y][Game::FIELD_SIZE.x];

	auto scoreDispBlack = std::make_unique<NumDisp<2>>(Vec2f{ +0.5f, 0.4f });
	auto scoreDispWhite = std::make_unique<NumDisp<2>>(Vec2f{ +0.5f, 0.2f });
	bool firstGameOver = true;
	int scorePoint = 0;

	// texture ids
	GLuint stoneId;
	GLuint numId;
}


//--------------------------------------------------------------------------------
// �G���[�R�[���o�b�N
void ErrorCallback(int error, const char* description)
{
	std::cerr << "Error Occured code: " << error << " desc: " << description << "\n";
}

//--------------------------------------------------------------------------------
// ���̓R�[���o�b�N
void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (action == GLFW_PRESS)
	{
		input.mKeyStates[key].pressed = true;
	}
	else if (action == GLFW_RELEASE)
	{
		input.mKeyStates[key].pressed = false;
	}

	// ESC�ŏI��
	if (input.mKeyStates[GLFW_KEY_ESCAPE].pressed)
	{
		glfwSetWindowShouldClose(window, true);
	}
}

//--------------------------------------------------------------------------------
// �J�[�\���ړ��R�[���o�b�N
void CursorPosCallBack(GLFWwindow* window, double xpos, double ypos)
{
	static double pastx = 0, pasty = 0;
	if (pastx == xpos && pasty == ypos)
	{
		return;
	}

	// �J�[�\���ʒu�X�V
	input.mCursorPos = { static_cast<int>(xpos), static_cast<int>(ypos) };
	//std::cout << "cursor pos x: " << xpos << " y: " << ypos << "\n";
}

//--------------------------------------------------------------------------------
// �}�E�X�N���b�N�R�[���o�b�N
void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
	if (action == GLFW_PRESS)
	{
		input.mMouseStates[button].pressed = true;
		//std::cout << "mouse " << button << " pressed!\n";
	}

	//if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS)
	//{

	//}
}

#ifdef _MSC_VER
#include <direct.h>
#define GetCurrentDir _getcwd
#else
#include <unistd.h>
#define GetCurrentDir getcwd
#endif

//--------------------------------------------------------------------------------
// ��ƃf�B���N�g���̎擾
std::string GetCurrentWorkingDir(void)
{
	char buff[FILENAME_MAX];
	GetCurrentDir(buff, FILENAME_MAX);
	std::string current_working_dir(buff);
	return current_working_dir;
}

//--------------------------------------------------------------------------------
// �`��
void Draw()
{
	// ��ʂ̏�����
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearDepth(1.0);

	game->Draw(stoneId);

	scoreDispBlack->Draw(numId);
	scoreDispWhite->Draw(numId);

}

//--------------------------------------------------------------------------------
// ���C�u�����̏�����
int LibInit()
{
	std::cout << "current directory is " << GetCurrentWorkingDir().c_str() << "\n";

	if (!glfwInit())
	{
		return -1;
	}

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
	window = glfwCreateWindow(WINDOW_SIZE.x, WINDOW_SIZE.y, GAME_TITLE, NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	glfwSetErrorCallback(ErrorCallback);
	glfwSetKeyCallback(window, KeyCallback);
	glfwSetCursorPosCallback(window, CursorPosCallBack);
	glfwSetMouseButtonCallback(window, MouseButtonCallback);

	// ���j�^�Ƃ̓���
	glfwMakeContextCurrent(window);
	auto addr = (GLADloadproc)glfwGetProcAddress;
	gladLoadGLLoader(addr);
	glfwSwapInterval(1);

	return 0;
}

// ������
void Init()
{
	game->ResetBoard();
	const auto& score = game->GetCurrentScore();
	scoreDispBlack->Update(score.x);
	scoreDispWhite->Update(score.y);

	// �u����ꏊ���n�C���C�g
	game->CheckPlayable();

	gameState = GameState::Main;
	std::cout << "Game Start!\n";
}

// ���C���̏���
void GameMain()
{
	// �N���b�N������
	if (input.mMouseStates[GLFW_MOUSE_BUTTON_LEFT].pressed)
	{
		// �΂�u��
		game->SetStone(input.mCursorPos);

		const auto& score = game->GetCurrentScore();
		scoreDispBlack->Update(score.x);
		scoreDispWhite->Update(score.y);


		// �u���Ȃ���΃p�X
		if (!game->CheckPlayable())
		{
			std::cout << "Unplayable. Turn changed.\n";
			game->SwitchTurn();
			// �ǂ�����u���Ȃ���΂����ŃQ�[���I�[�o�[
			if (!game->CheckPlayable())
			{
				std::cout << "Game is over. score - black: " << score.x << " white: " << score.y << "\n";

				if (score.x > score.y)
				{
					std::cout << "Black Win!\n";
				}
				else if (score.y > score.x)
				{
					std::cout << "White Win!\n";
				}
				else
				{
					std::cout << "Draw game.\n";
				}

				std::cout << "Press R to retry.\n";
				gameState = GameState::Gameover;
				return;
			}
		}
	}

	// �Q�[������R�ōŏ�����
	if (input.mKeyStates[GLFW_KEY_R].pressed)
	{
		gameState = GameState::Init;
	}

}

// �Q�[���I�[�o�[
void GameOver()
{
	if (input.mKeyStates[GLFW_KEY_R].pressed)
	{
		gameState = GameState::Init;
	}
}

//--------------------------------------------------------------------------------
// ENTRY POINT
int main()
{
	if (LibInit())
	{
		return -1;
	}

	// shader
	shader.SetUp();

	// load images
	stoneId = LoadBmp("images/othello.bmp");
	numId = LoadBmp("images/num.bmp");

	// init board
	game = std::make_unique<Game>();

	// �Q�[�����[�v
	while (!glfwWindowShouldClose(window))
	{
		// -- �v�Z --
		switch (gameState)
		{
		case GameState::Init:
			Init();
			break;
		case GameState::Main:
			GameMain();
			break;
		case GameState::Gameover:
			GameOver();
			break;
		default:
			std::cout << "unknown state\n";
			break;
		}

		input.Update();
		input.ResetNow();

		// -- �`�� -- 
		Draw();

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwTerminate();

	return 0;
}