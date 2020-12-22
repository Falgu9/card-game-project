#include <iostream>
#include "Card.h"

std::string Card::rankAsStr[13] = { "Ace", "2", "3", "4", "5", "6", "7", "8","9", "10", "Jack", "Queen", "King" };
std::string Card::suitAsStr[4] = { "Spade", "Heart", "Club", "Diamond" };

Card::Card() : rank(0), suit(0) {}

Card::Card(int rank, int suit) : rank(0), suit(0)
{
	if(rank >= 1 && rank <= 13 && suit >=1 && suit <= 4)
	{
		this -> rank = rank;
		this -> suit = suit;
	}
}

void Card::setRank(int r) { rank = r; }
void Card::setSuit(int s) { suit = s; }

int Card::getRank() const { return rank; }
int Card::getSuit() const { return suit; }

std::ostream& operator<<(std::ostream& os, const Card& card) {
	return os << card.rankAsStr[card.getRank() - 1] << " of " << card.suitAsStr[card.getSuit()] << std::endl;
}