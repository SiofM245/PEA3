#include "randomGenerator.h"
#include <stdlib.h>
#include <time.h>

RandomGenerator::RandomGenerator() {
	// Ziarno pocz�tkowe generatora losowane za pomoc� standardowej
	// funkcji rand() z C
	srand(time(NULL));
	generatorSeed = rand();
}

// Generowanie liczb pseudolosowych za pomoc� algorytmu wyhash
uint32_t RandomGenerator::rnd() {
	generatorSeed += 0xe120fc15;
	uint64_t tmp;
	tmp = (uint64_t)generatorSeed * 0x4a39b70d;
	uint32_t m1 = (tmp >> 32) ^ tmp;
	tmp = (uint64_t)m1 * 0x12fad5c9;
	uint32_t m2 = (tmp >> 32) ^ tmp;
	return m2;
}

// Generowanie liczb pseudolosowych z przedzia�u od min (w��cznie) do max (wy��cznie)
int RandomGenerator::randInt(int min, int max) {
	return (rnd() % (max - min)) + min;
}