#include "adder.h"

#include <iostream>
#include <assert.h>

int main() {
    int a = 5;
    int b = 3;
 //   assert((5+3) == logical_add(a, b));
    std::cout << logical_add(a, b) << std::endl;

    return 0;
}