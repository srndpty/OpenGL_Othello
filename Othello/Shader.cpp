#include "glad/glad.h"
#include "GLFW/glfw3.h"
#include <string>
#include <iostream>

#include "Shader.h"

const char* Shader::ID_position = "position";
const char* Shader::ID_uv = "uv";
const char* Shader::ID_texture = "texture";
const char* Shader::ID_MVP = "MVP";
const char* Shader::ID_color = "color";

//--------------------------------------------------------------------------------
Shader::Shader()
{
}


//--------------------------------------------------------------------------------
Shader::~Shader()
{
}

//--------------------------------------------------------------------------------
void Shader::SetUp()
{
	//static const int VERTEX_BUFFER_COUNT = 4;
	//GLuint vertexBuffers[VERTEX_BUFFER_COUNT];
	//glGenBuffers(VERTEX_BUFFER_COUNT, vertexBuffers);
	//�o�[�e�b�N�X�V�F�[�_�̃R���p�C��
	auto vShaderId = glCreateShader(GL_VERTEX_SHADER);
	std::string vertexShader = R"#(
	uniform mat4 MVP;
	attribute vec3 position;
	attribute vec2 uv;
	attribute vec4 color;
	varying vec4 vcolor;
	varying vec2 vuv;
	void main(void){
		gl_Position = MVP * vec4(position, 1.0);
		vuv = uv;
		vcolor = color;
	}
	)#";
	const char* vs = vertexShader.c_str();
	glShaderSource(vShaderId, 1, &vs, NULL);
	glCompileShader(vShaderId);

	//�t���O�����g�V�F�[�_�̃R���p�C��
	GLuint fShaderId = glCreateShader(GL_FRAGMENT_SHADER);
	std::string fragmentShader = R"#(
	varying vec2 vuv;
	varying vec4 vcolor;
	uniform sampler2D texture;
	void main(void){
		gl_FragColor = texture2D(texture, vuv) * vcolor;
	}
	)#";
	const char* fs = fragmentShader.c_str();
	glShaderSource(fShaderId, 1, &fs, NULL);
	glCompileShader(fShaderId);

	//�v���O�����I�u�W�F�N�g�̍쐬
	GLuint programId = glCreateProgram();
	glAttachShader(programId, vShaderId);
	glAttachShader(programId, fShaderId);

	// �����N
	glLinkProgram(programId);

	glUseProgram(programId);

	mProgramId = programId;
	// ���Ԗڂ�attribute�ϐ���
	mPositionLocation = glGetAttribLocation(programId, Shader::ID_position);
	if (mPositionLocation == -1)
	{
		std::cerr << "glGetAttribLocation failed " << Shader::ID_position << "\n";
	}
	mUvLocation       = glGetAttribLocation(programId, Shader::ID_uv);
	if (mUvLocation == -1)
	{
		std::cerr << "glGetAttribLocation failed " << Shader::ID_uv << "\n";
	}
	mTextureLocation  = glGetUniformLocation(programId, Shader::ID_texture);
	if (mTextureLocation == -1)
	{
		std::cerr << "glGetUniformLocation failed " << Shader::ID_texture << "\n";
	}
	mMvpLocation      = glGetUniformLocation(programId, Shader::ID_MVP);
	if (mMvpLocation == -1)
	{
		std::cerr << "glGetUniformLocation failed " << Shader::ID_MVP << "\n";
	}
	mColorLocation    = glGetAttribLocation(programId, Shader::ID_color);
	if (mColorLocation == -1)
	{
		std::cerr << "glGetAttribLocation failed " << Shader::ID_color << "\n";
	}

	// attribute������L���ɂ���
	glEnableVertexAttribArray(mPositionLocation);
	glEnableVertexAttribArray(mUvLocation);
	glEnableVertexAttribArray(mMvpLocation);
	glEnableVertexAttribArray(mColorLocation);

	// uniform������ݒ肷��
	glUniform1i(mTextureLocation, 0);

}
