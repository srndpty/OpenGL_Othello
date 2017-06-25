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

#pragma comment(lib, "opengl32.lib")

Input input;
Shader shader;
Random random;

namespace
{
	const char* GAME_TITLE = "Othello Game";

	GLFWwindow* window = nullptr;
	auto scoreDisp = std::make_unique<NumDisp<4>>(Vec2f{ +0.5f, 0.4f });
	auto stone = std::make_unique<Stone>(Vec2f{ 0, 0 }, Vec2f{ 0.2f, 0.2f });
	bool firstGameOver = true;
	int scorePoint = 0;
	GLuint stoneId;
	GLuint numId;
}


//--------------------------------------------------------------------------------
// �G���[�R�[���o�b�N
void ErrorCallback2(int error, const char* description)
{
	std::cerr << "Error Occured code: " << error << " desc: " << description << "\n";
}

//--------------------------------------------------------------------------------
// ���̓R�[���o�b�N
void KeyCallback2(GLFWwindow* window, int key, int scancode, int action, int mods)
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
// ���͂���̏���
void ProcessInputs()
{
	// ���E�ړ�
	//if (input.GetButtomDown(GLFW_KEY_A))
	//{
	//	// ��
	//	if (game->IsMovable(*current, -1, 0))
	//	{
	//		current->Move({ -1, 0 });
	//	}
	//}
}



//--------------------------------------------------------------------------------
// �`��
void Draw()
{
	// ��ʂ̏�����
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearDepth(1.0);

	stone->Draw(stoneId);
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

	glfwSetErrorCallback(ErrorCallback2);
	glfwSetKeyCallback(window, KeyCallback2);

	// ���j�^�Ƃ̓���
	glfwMakeContextCurrent(window);
	auto addr = (GLADloadproc)glfwGetProcAddress;
	gladLoadGLLoader(addr);
	glfwSwapInterval(1);

	return 0;
}

//--------------------------------------------------------------------------------
// ENTRY POINT
int main()
{
	if (LibInit())
	{
		return -1;
	}

	shader.SetUp();

	stoneId = LoadBmp("images/othello.bmp");
	numId = LoadBmp("images/num.bmp");

	// �Q�[�����[�v
	while (!glfwWindowShouldClose(window))
	{
		// -- �v�Z --
		scoreDisp->Update(scorePoint);
		//if (game->IsGameOver())
		//{
		//	ProcessGameover();
		//}
		//else
		{
			// �S�̏���
			//game->Process();
			ProcessInputs();
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