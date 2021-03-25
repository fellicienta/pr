#include <stdint.h>
#include <random>
#include "coins.h"

uint16_t flip_a_coin() {
	static std::random_device rd;
	static std::mt19937 g(rd());

	return rd() % 2;
}

uint16_t play(const uint16_t REQUIRED) {
	uint16_t counter = 1, fling;
	uint16_t first_value = flip_a_coin(), new_value;

	for (fling = 2; REQUIRED != counter; ++fling) {
		new_value = flip_a_coin();

		if (new_value == first_value) {
			++counter;
		}
		else {
			counter = 1;
			first_value = new_value;
		}
	}

	return fling;
}