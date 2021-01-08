#include <iostream>
#include "Card.h"

std::string Card::ranks[14] = {"Ace", "2", "3", "4", "5", "6", "7", "8", "9", "10", "Jack", "Queen", "King", "Joker"};
std::string Card::suits[4] = {"Spade", "Heart", "Club", "Diamond"};

Card::Card() : rank(0), suit(0),value(0), symbol("nothing") {}

Card::Card(int rank, int suit) : rank(0), suit(0), value(0)
{
	this->rank = rank;
	this->suit = suit;

	if (rank == 13)
		this->suit = -1;
}

Card::Card(int rank, int suit, std::string symbol) : rank(0), suit(0), symbol(symbol)
{
	this->rank = rank;
	this->suit = suit;
	this->symbol = symbol;
}

Card::Card(int rank, int suit, int value, std::string symbol) : rank(rank), suit(suit), value(value), symbol(symbol)
{
	if (suit == 0)
	{
		couleur = "coeur";
	}
	else if (suit == 1)
	{
		couleur = "carreau";
	}
	else if (suit == 2)
	{
		couleur = "trefle";
	}
	else if (suit == 3)
	{
		couleur = "pique";
	}
}

Card::Card(int rank, int suit, int value) : rank(0), suit(0), value(0)
{
	this->rank = rank;
	this->suit = suit;
	this->value = value;

	if (rank == 13)
	{
		this->rank = 13;
		this->suit = -1;
	}
}

int Card::getRank() const { return rank; }
int Card::getSuit() const { return suit; }
std::string Card::getSymbol() const { return symbol; }
int Card::getValue() const { return value; }
std::string Card::getCouleur() const { return couleur; }

void Card::setRank(int rank) { this->rank = rank; }
void Card::setSuit(int suit) { this->suit = suit; }
void Card::setSymbol(std::string symbol) { this->symbol = symbol; }
void Card::setValue(int value) { this->value = value; }

bool Card::operator<=(const Card &a) const { return value <= a.value; }
bool Card::operator>=(const Card &a) const { return value >= a.value; }
bool Card::operator<(const Card &a) const { return value < a.value; }
bool Card::operator>(const Card &a) const { return value > a.value; }
bool Card::operator==(const Card &a) const { return value == a.value; }
bool Card::operator!=(const Card &a) const { return value != a.value; }

std::ostream &operator<<(std::ostream &os, Card const &card)
{
	os << card.getSymbol() << " de " << card.getCouleur() << " ->  rang : " << card.getRank() << " | valeur : " << card.getValue() << std::endl;
	return os;
}