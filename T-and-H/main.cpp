#include <iostream>
#include <unistd.h>
#include "lib.h"

int main () {
    Tortoise T;
    Hare H;
    uint16_t value;
    bool t_winner = false;
    bool h_winner = false;

    std::cout << "BANG !!!!!" << std::endl;
    std::cout << "AND THEY'RE OFF !!!!!" << std::endl;
    std::cout << "TH" << std::endl;

    for ( ; ;) {
        sleep(1);
        value = rand_value();
        T.action(value);
        H.action(value);
        print_line(T.get_position(), H.get_position());     
        t_winner = T.is_winner();
        h_winner = H.is_winner();

        if (t_winner && h_winner) {
            std::cout << "FRIENDSHIP WINS !!!!!!!!" << std::endl;
            break;
        }   
        else if (t_winner) {
            std::cout << "TORTOISE WINS!!! YAY!!" << std::endl;
            break;
        } 
        else if (h_winner) {
            std::cout << "HARE WINS!!! YUCH!!" << std::endl;
            break;
        } 
    }

    return 0;
}

