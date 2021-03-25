#include <iostream>
#include <vector>
#include <string>
#include "cards.h"

int main() {
	std::vector<Card> deck(36);
	const std::vector<std::string> face = { "Ace", "Six", "Seven", "Eight", "Nine",
										"Ten", "Jack", "Qween", "King" };
	const std::vector<std::string> suit = { "Hearts", "Diamonds", "Clubs", "Spades" };

	fillDeck(deck, face, suit);
	shuffle(deck);
	double probability = get_probability(deck);

	std::cout << probability << std::endl;

	return 0;
}

