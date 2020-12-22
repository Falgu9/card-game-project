#ifndef __DECK__H__
#define __DECK__H__

#include "Card.h"
#include "Stack.h"

const int DEFAULT_DECK_SIZE = 52;

class Deck
{
	friend std::ostream& operator<<(std::ostream& os, const Deck& deck);

private:	
	Stack<Card*> *deck;
	void swap(Card *card1, Card *car2);
	
public:
	Deck();
	~Deck();
	Deck(Deck const& copy);

	Deck& operator=(Deck const& copy);

	Stack<Card*> *getDeck() const;

	Deck* shuffle();
	Card* deal();
	Deck* placeBack(Card* card);
};

#endif

