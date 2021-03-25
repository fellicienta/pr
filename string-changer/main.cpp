#include <iostream>
#include <string>
#include <assert.h>
#include "function.h"

int main() {
	std::string original = random_string();
	std::string copy = original; 
	word_order_changer(original);
	word_order_changer(original);

	assert(original == copy);
    std::cout << "It's working!\n";
	return 0;
}