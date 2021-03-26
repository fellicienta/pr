#include <random>
#include <iostream>
#include "lib.h"

uint16_t rand_value() {
	static std::random_device rd;
	static std::mt19937 g(rd());

	return rd() % 10 + 1;
}

void print_line(uint16_t t_position, uint16_t h_position) {
    for (uint16_t i = 1; i <= 70; ++i) {
        if(i < t_position && i < h_position)
            std::cout << ' ';
        else if (i == t_position && i == h_position)
            std::cout << "OUCH!!!";
        else if (i == t_position)
            std::cout << 'T';
        else if (i == h_position)
            std::cout << 'H';
        else if (i != t_position && i != h_position)
            std::cout << ' ';
    }
        std::cout << "|>" << std::endl;

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
                break;
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

bool Tortoise::is_winner() {
    return position == 70;
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

bool Hare::is_winner() {
    return position == 70;
}