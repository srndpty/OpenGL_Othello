// Loader.h
// 画像の読み込みをまとめる

#pragma once

#include "GLFW/glfw3.h"
#include "glad/glad.h"
#include <iostream>
#include <fstream>

// bmp画像の読み込み
GLuint LoadBmp(const char* filename)
{
	static constexpr int bmpHeaderSize = 54;
	char header[bmpHeaderSize];
	// テクスチャIDの生成
	GLuint id;
	glGenTextures(1, &id);

	// ファイルの読み込み
	std::ifstream fstr(filename, std::ios::binary);
	if (!fstr)
	{
		std::cout << "Failed to load " << filename << "\n";
		return -1;
	}

	fstr.read(header, bmpHeaderSize);
	if (header[0] != 'B' || header[1] != 'M')
	{
		printf("Not a correct BMP file\n");
		return 0;
	}
	int dataPos = *(int*)&(header[0x0A]);
	int imageSize = *(int*)&(header[0x22]);
	int width = *(int*)&(header[0x12]);
	int height = *(int*)&(header[0x16]);
	if (imageSize == 0)    imageSize = width*height * 3; // 3 : one byte for each Red, Green and Blue component
	if (dataPos == 0)      dataPos = 54; // The BMP header is done that way


	const size_t fileSize = static_cast<size_t>(fstr.seekg(0, fstr.end).tellg());
	fstr.seekg(0, fstr.beg);
	if (fileSize >= std::numeric_limits<size_t>::max())
	{
		std::cout << "Failed to get filesize that must be less than size_t max";
	}
	char* textureBuffer = new char[fileSize];
	fstr.read(textureBuffer, fileSize);

	// テクスチャをGPUに転送
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glBindTexture(GL_TEXTURE_2D, id);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, width, height, 0, GL_BGR, GL_UNSIGNED_BYTE, textureBuffer + dataPos);

	// テクスチャの設定
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// テクスチャのアンバインド
	delete[] textureBuffer;
	glBindTexture(GL_TEXTURE_2D, 0);

	return id;
}
