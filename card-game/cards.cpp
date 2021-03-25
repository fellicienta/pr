#include <random>
#include <vector>
#include <string>
#include "cards.h"

double get_probability(std::vector<Card> & deck) {
	uint16_t counter = 0;

	for (uint16_t deal = 0; deal < 1000; ++deal) {
		for (uint16_t i = 0; i < 6; ++i) {
			shuffle(deck);

			if (deck.at(i).face == "Ace" && deck.at(i).suit == deck.at(7).suit)
				counter++;
		}
	}

	return counter / 1000.0;
}

void fillDeck(std::vector<Card> & deck, const std::vector<std::string> & face, const std::vector<std::string> & suit) {

	for (uint16_t i = 0; i < 36; ++i)
	{
		deck.at(i).face = face.at(i % 9);
		deck.at(i).suit = suit.at(i / 9);
	}
}

void shuffle(std::vector<Card> & deck) {
	static std::random_device rd;
	static std::mt19937 g(rd());

	for (uint16_t i = 0; i < 36; ++i)
		std::swap(deck.at(i), deck.at(rd() % 36));
}