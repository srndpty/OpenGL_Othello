// Util.cpp
// ユーティリティ関数の集まり

#include "Util.h"

#include <string>

uint32_t PowI(uint32_t base, uint32_t num)
{
	uint32_t ret = 1;
	for (size_t i = 0; i < num; i++)
	{
		ret *= base;
	}
	return ret;
}

uint32_t Pow10(uint32_t num)
{
	return PowI(10, num);
}

#ifdef _MSC_VER
#include <direct.h>
#define GetCurrentDir _getcwd
#else
#include <unistd.h>
#define GetCurrentDir getcwd
#endif

//----------------------------------------
// 作業ディレクトリの取得
std::string GetCurrentWorkingDir()
{
	char buff[FILENAME_MAX];
	GetCurrentDir(buff, FILENAME_MAX);
	std::string current_working_dir(buff);
	return current_working_dir;
}

