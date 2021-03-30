#include "adder.h"

#include <stdint.h>

template <typename T>
T logical_add(T number1, T number2) {
    uint32_t size = sizeof(int) * 8;  //quantity of bits
    uint32_t x = number1 & 0x01;
    uint32_t y = number2 & 0x01;
    uint32_t z;
    uint32_t result = 0;
    uint32_t q = 0;

    for (uint32_t i = 0; i < size; ++i) {
        z = x ^ y ^ q;
        result += (z << i);

        q = x & y ^ (x ^ y) & q; 
        x = (number1 >> 1) & 0x01;
        y = (number2 >> 1) & 0x01;
    }

    z = q;
// ?    result += (z << 32);

    return result;
}