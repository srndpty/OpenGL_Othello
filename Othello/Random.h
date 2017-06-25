// Random.h
// ������\������

#pragma once

#include <cstdint>

class Random
{
private:
	// �����̓������l
	uint32_t x = 123456789;
	uint32_t y = 362436069;
	uint32_t z = 521288629;
	uint32_t w = 88675123;

public:
	/// special
	Random();
	Random(uint32_t aX, uint32_t aY, uint32_t aZ, uint32_t aW);
	~Random();

	/// normal
	uint32_t operator ()();                           // �����̎擾 [0 - uint32_t max]
	uint32_t operator ()(uint32_t max);               // �����̎擾 [0 - max)
	uint32_t operator ()(uint32_t min, uint32_t max); // �����̎擾 [min - max]

	uint32_t Next();							// �����̎擾 [0 - uint32_t max]
	uint32_t Next(uint32_t max);				// �����̎擾 [0 - max)
	uint32_t Next(uint32_t min, uint32_t max);	// �����̎擾 [min - max]
};

