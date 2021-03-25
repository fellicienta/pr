#include <iostream>
#include <random>
#include "coins.h"

int main() {
	const uint16_t REQUIRED = 11;
	const uint16_t quantity = 1000;
	uint32_t average = 0;

	for (uint16_t i = 0; i < quantity; ++i) {
		average += play(REQUIRED);
	}

	average /= quantity;
	std::cout << "Average : " << average << std::endl;

    return 0;
}

