#ifndef __DECK__H__
#define __DECK__H__

#include "Card.h"
#include <stack>
#include <iostream>

class Deck
{
	friend std::ostream &operator<<(std::ostream &os, Deck const &deck);

private:
	int deckSize;
	std::stack<Card *> *deck;
	void swap(Card *card1, Card *car2);

public:
	Deck();
	Deck(int capacity);
	Deck(int defaultDeckSize, int numberOfDeck, bool jokers);
	~Deck();
	Deck(Deck const &copy);

	Deck &operator=(Deck const &copy);

	std::stack<Card *> *getDeck() const;
	int getDeckSize() const;

	void setDeckSize(int deckSize);

	void shuffle();
	Card *deal();
	void placeBack(Card *card);
};

#endif
