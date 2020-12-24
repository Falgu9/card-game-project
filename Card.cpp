#include <iostream>
#include "Card.h"

std::string Card::ranks[13] = { "Ace", "2", "3", "4", "5", "6", "7", "8","9", "10", "Jack", "Queen", "King" };
std::string Card::suits[4] = { "Spade", "Heart", "Club", "Diamond" };

Card::Card() : rank(0), suit(0) {}

Card::Card(int rank, int suit) : rank(0), suit(0), value(0)
{
	if(rank >= 0 && rank < 13 && suit >= 0 && suit < 4)
	{
		this -> rank = rank;
		this -> suit = suit;
	}
}

Card::Card(int rank, int suit, int value) : rank(0), suit(0), value(0)
{
	if(rank >= 0 && rank < 13 && suit >= 0 && suit < 4 && value >= 1 && value < 14)
	{
		this -> rank = rank;
		this -> suit = suit;
		this -> value = value;
	}
}

int Card::getRank() const { return rank; }
int Card::getSuit() const { return suit; }
int Card::getValue() const { return value; }

void Card::setRank(int rank) { this -> rank = rank; }
void Card::setSuit(int suit) { this -> suit = suit; }
void Card::setValue(int value) { this -> value = value; }

bool Card::operator<=(const Card& a) const { return value <= a.value; }
bool Card::operator>=(const Card& a) const { return value >= a.value; }
bool Card::operator<(const Card& a) const { return value < a.value; }
bool Card::operator>(const Card& a) const { return value > a.value; }
bool Card::operator==(const Card& a) const { return value == a.value; }
bool Card::operator!=(const Card& a) const { return value != a.value; }

std::ostream& operator<<(std::ostream& os, Card const& card) {
	return os << card.ranks[card.getRank()] << " of " << card.suits[card.getSuit()] << std::endl;
}