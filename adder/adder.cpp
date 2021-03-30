#include "adder.h"

#include <stdint.h>


uint32_t logical_add(uint32_t number1, uint32_t number2) {
    uint32_t size = sizeof(int) * 8;  //quantity of bits
 //   uint32_t mask = 1;
    uint32_t x;
    uint32_t y;
    uint32_t z;
    uint32_t result = 0;
    uint32_t q = 0;

    for (uint32_t i = 0; i < size; ++i) {
        x = number1 & 0x01;
        y = number2 & 0x01;
        z = x ^ y ^ q;
        result += (z << i);

        q = x & y ^ (x ^ y) & q; 
        number1 >>= 1;
        number2 >>= 1;
    }

    z = q;
// ?    result += (z << 32);

    return result;
}