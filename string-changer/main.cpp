#include <iostream>
#include <string>
#include <assert.h>
#include "function.h"

int main() {
	std::string original = random_string();
	
	std::string reversed = word_order_changer(original);

	std::string get_origin = word_order_changer(reversed);

	assert(original == get_origin);
    std::cout << "It's working!\n";
	return 0;
}