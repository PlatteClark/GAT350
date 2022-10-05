#pragma once
#include <random>

namespace squampernaut
{
	inline void seedRandom(int seed) { srand(seed); }

	inline int random() { return rand(); }
	inline int random(int max) { return random() % max; } // exclusive
	inline int random(int min, int max) { return min + rand() % ((max - min) + 1); }

	inline float randomF() { return rand() / (float)RAND_MAX; } // returns value between 0.0 and 1.0
	inline float randomF(float max) { return randomF() * max; } //returns value between 0 and max
	inline float randomF(float min, float max) { return min + randomF(max - min); }
}