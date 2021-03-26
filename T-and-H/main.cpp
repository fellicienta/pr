#include <iostream>
#include <unistd.h>
#include "lib.h"

int main () {
    Tortoise T;
    Hare H;
    uint16_t value;
    std::cout << "BANG !!!!!" << std::endl;
    std::cout << "AND THEY'RE OFF !!!!!" << std::endl;

    for (int i = 0; i < 10; ++i) {
        sleep(1);
        value = rand_value();
        T.action(value);
        H.action(value);
        print_line(H.get_position(), H.get_position());        
    }

    return 0;
}

