#pragma once
#include <stdint.h>

class RandomGenerator {
	int min = 0;
	int max = 0;
	uint32_t generatorSeed;
	uint32_t rnd();

public:
	RandomGenerator();
	int randInt(int min, int max);
};