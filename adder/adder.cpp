#include "adder.h"

#include <stdint.h>
#include <random>

int32_t logical_add(int32_t number1, int32_t number2) {
    uint32_t x;
    uint32_t y;
    int32_t result = 0;
    uint32_t q = 0;

    for (uint32_t i = 0; i < 32; ++i) {
        x = (number1 >> i) & 0x01;
        y = (number2 >> i) & 0x01;
        result += ((x ^ y ^ q) << i);
        q = x & y ^ (x ^ y) & q;      
    }

    return result;
}

int32_t rand_number() {
    static std::random_device rd;
    static std::mt19937 g(rd());

    return rd() % 10000;
}