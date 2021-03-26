#pragma once
#include <stdint.h>

uint16_t rand_value();

class Tortoise 
{
public:
    void action(uint16_t value);
    void fast_plod();
    void slip();
    void slow_plod();
    uint16_t get_position();
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
    uint16_t get_position();
private:
    uint16_t position = 1;
};

