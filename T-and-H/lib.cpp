#include <random>
#include <stdint.h>
#include "lib.h"

uint16_t rand_value() {
	static std::random_device rd;
	static std::mt19937 g(rd());

	return rd() % 10 + 1;
}

void Tortoise::action(uint16_t value) {
    switch(value) {
        case 1:
        case 2:
        case 3:
        case 4:
        case 5: fast_plod();
                break;
        case 6:
        case 7: slip();
                break;
        case 8:
        case 9:
        case 10: slow_plod();
    }
}

void Tortoise::fast_plod() {    // 3 squares to the right
    position += 3;
}

void Tortoise::slip() {     // 6 squares to the left
    position > 6 ? position -= 6 : position = 1;
}

void Tortoise::slow_plod() {     // 1 square to the right
    position += 1;
}

uint16_t Tortoise::get_position() {
    return position;
}

void Hare::action(uint16_t value) {
    switch(value) {
        case 1:
        case 2: sleep();
                break;
        case 3:
        case 4: big_hop();
                break;
        case 5: big_slip();
                break;
        case 6:
        case 7: 
        case 8: small_hop();
                break;
        case 9:
        case 10: small_slip();
                break;
    }
}

void Hare::sleep() {    // no move at all
}

void Hare::big_hop() {      // 9 squares to the right
    position += 9;
}

void Hare::big_slip() {     // 12 squares to the left
    position > 12 ? position -= 12 : position = 1;
}

void Hare::small_hop() {      // 1 square to the right
    position += 1;
}

void Hare::small_slip() {     // 2 squares to the left
    position > 2 ? position -= 2 : position = 1;
}

uint16_t Hare::get_position() {
    return position;
}