#include "randomGenerator.h"
#include <stdlib.h>
#include <time.h>

RandomGenerator::RandomGenerator() {
	// Ziarno pocz¹tkowe generatora losowane za pomoc¹ standardowej
	// funkcji rand() z C
	srand(time(NULL));
	generatorSeed = rand();
}

// Generowanie liczb pseudolosowych za pomoc¹ algorytmu wyhash
uint32_t RandomGenerator::rnd() {
	generatorSeed += 0xe120fc15;
	uint64_t tmp;
	tmp = (uint64_t)generatorSeed * 0x4a39b70d;
	uint32_t m1 = (tmp >> 32) ^ tmp;
	tmp = (uint64_t)m1 * 0x12fad5c9;
	uint32_t m2 = (tmp >> 32) ^ tmp;
	return m2;
}

// Generowanie liczb pseudolosowych z przedzia³u od min (w³¹cznie) do max (wy³¹cznie)
int RandomGenerator::randInt(int min, int max) {
	return (rnd() % (max - min)) + min;
}