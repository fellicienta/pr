#include "adder.h"

#include <stdint.h>
#include <random>

int32_t logical_add(int32_t number1, int32_t number2) {
//  uint32_t size = sizeof(T) * 8;  //quantity of bits
    uint32_t x = number1 & 0x01;
    uint32_t y = number2 & 0x01;
    uint32_t z;
    int32_t result = 0;
    uint32_t q = 0;

    for (uint32_t i = 0; i < 32; ++i) {
        x = (number1 >> i) & 0x01;
        y = (number2 >> i) & 0x01;
//        x = number1 & 0x01;
//        y = number2 & 0x01;
        z = x ^ y ^ q;
        result += (z << i);

        q = x & y ^ (x ^ y) & q; 
//        number1 >>= 1;
 //       number2 >>= 1;
        
    }

//  z = q;
//? result += (z << 32);

    return result;
}

int32_t rand_number() {
    static std::random_device rd;
    static std::mt19937 g(rd());

    return rd() % INT32_MAX + 1;
}