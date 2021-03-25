#pragma once
#include <string>
#include <vector>

struct Card
{
	std::string face;
	std::string suit;
};

void fillDeck(std::vector<Card> & deck, const std::vector<std::string> & face, const std::vector<std::string> & suit);
void shuffle(std::vector<Card> & deck);
double get_probability(std::vector<Card> & deck);