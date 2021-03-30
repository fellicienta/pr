#include "adder.h"

#include <stdint.h>

int logical_add(int number1, int number2) {
    uint32_t size = sizeof(int) * 8;  //quantity of bits
    int mask = 1;
    int q = 0;
    int x;
    int y;
    int z;
    int result = 0;

    for (int i = 0; i < size; ++i) {
        x = number1 & mask;
        y = number2 & mask;
        z = x ^ y ^ q;
        result += (z << i);

        q = x & y ^ (x ^ y) & q; 
        number1 >>= 1;
        number2 >>= 1;
    }

    z = q;
 //   result += (z << 31);

    return result;
}