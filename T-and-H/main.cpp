#include <iostream>
#include <unistd.h>
#include "lib.h"

int main () {
    Tortoise T;
    Hare H;
    uint16_t value;
    std::cout << "BANG !!!!!" << std::endl;
    std::cout << "AND THEY'RE OFF !!!!!" << std::endl;

    for ( ; ; ) {
        sleep(1);
        value = rand_value();
        T.action(value);
        H.action(value);
    }

    return 0;
}

void print_line(uint16_t t_position, uint16_t h_position) {
    for (uint16_t i = 1; i <= 70; ++i) {
        if (t_position == h_position)
            std::cout << "OUCH!!!";
    }
}