#include "function.h"

#include <string>
#include <random>


std::string word_order_changer(std::string s) {
	std::string new_str;
	size_t position;

	while (!s.empty()) {
		position = s.find_last_of(' ');

		if (position == s.npos)
			break;

		new_str.append(s.substr(position + 1));
		new_str.append(" ");
		s.erase(position, s.length() - 1);
	}

	new_str.append(s);

	return new_str;
}

std::string random_string() {
	std::random_device rd;
	std::mt19937 g(rd());

	std::string result;
	int count = rd() % 9 + 1;

	for (int i = 0; i <= count; ++i)
	{
		result.append(random_word());

		if (i != count)
			result.append(" ");
	}
	return result;
}

std::string random_word()
{
	std::random_device rd;
	std::mt19937 g(rd());

	std::string result;
	int count = rd() % 9 + 1;

	for (int i = 0; i < count; ++i)
	{
		result.push_back((rd() % 26) + 'a');
	}
	return result;
}