#include <iostream>
#include <unistd.h>
#include "lib.h"

int main () {
    Tortoise T;
    Hare H;
    uint16_t value;
    std::cout << "BANG !!!!!" << std::endl;
    std::cout << "AND THEY'RE OFF !!!!!" << std::endl;

    for ( ; ;) {
        sleep(1);
        value = rand_value();
        T.action(value);
        H.action(value);
        print_line(T.get_position(), H.get_position());     

        if (T.is_winner() && H.is_winner()) {
            std::cout << "FRIENDSHIP WINS !!!!!!!!" << std::endl;
            break;
        }   
        else if (T.is_winner()) {
            std::cout << "TORTOISE WINS!!! YAY!!" << std::endl;
            break;
        } 
        else if (H.is_winner()) {
            std::cout << "HARE WINS!!! YUCH!!" << std::endl;
            break;
        } 
    }

    return 0;
}

