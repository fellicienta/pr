#pragma once
#include <stdint.h>

uint16_t rand_value();
void print_line(uint16_t t_position, uint16_t h_position);

class Tortoise 
{
public:
    void action(uint16_t value);
    void fast_plod();
    void slip();
    void slow_plod();
    uint16_t get_position();
    bool is_winner();
private:
    uint16_t position = 1;
};

class Hare
{
public:
    void action(uint16_t value);
    void sleep();
    void big_hop();
    void big_slip();
    void small_hop();
    void small_slip();
    bool is_winner();
    uint16_t get_position();
private:
    uint16_t position = 1;
};

