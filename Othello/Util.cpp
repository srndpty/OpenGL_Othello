#include "Util.h"

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