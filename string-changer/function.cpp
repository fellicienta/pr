#include "function.h"

#include <string>
#include <random>
#include <algorithm>
#include <iterator>

void word_order_changer(std::string& s) {
	if (s.empty() || s.find(' ') == s.npos)
		return;

	auto begin = s.begin();
	auto end = s.end();
	std::reverse(begin, end);
	auto current = std::find(begin, end, ' ');

	while (current != end) {
		std::reverse(begin, current);
		begin = current + 1;
		current = std::find(begin, end, ' ');
	}

	std::reverse(begin, end);
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