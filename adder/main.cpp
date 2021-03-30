#include "adder.h"

#include <iostream>
#include <assert.h>

int main() {
    int a;
    int b;

    std::cin >> a >> b;

    assert((a + b) == logical_add(a, b));
    std::cout << logical_add(a, b) << std::endl;

    return 0;
}