#include <ctime>
#include <cstdlib>
#include "Deck.h"

Deck::Deck() : deck(0)
{
	deck = new Stack<Card*>(DECK_SIZE);

	for(int i = 0; i < 4; i++)
		for(int j = 0; j < 13; j++)
			deck -> push(new Card(j, i, j + 1));
}

Deck::~Deck() { delete deck; }

Deck::Deck(Deck const& copy)
{
	deck = new Stack<Card*>(*(copy.deck));
}

Deck& Deck::operator=(Deck const& copy)
{
	if(this != &copy)
	{
		delete deck;
		deck = new Stack<Card*>(*(copy.deck));
	}

	return *this;
}

Card* Deck::deal()
{
	return deck -> pop();
}

Deck* Deck::placeBack(Card *card)
{
	deck -> push(card);
	return this;
}

Deck* Deck::shuffle()
{
	Card* tmp[DECK_SIZE];

	for (int i = 0; i < DECK_SIZE; i++)
		tmp[i] = deck -> pop();

	srand((unsigned int)time(NULL));

	for (int i = 0; i < 500; i++)
		swap(tmp[rand() % DECK_SIZE], tmp[rand() % DECK_SIZE]);

	for (int i = 0; i < DECK_SIZE; i++)
		deck -> push(tmp[i]);

	return this;
}

void Deck::swap(Card *card1, Card *card2)
{
	Card temp = *card1;
	*card1 = *card2;
	*card2 = temp;
}

Stack<Card*> *Deck::getDeck() const { return deck; }

std::ostream& operator<<(std::ostream& os, Deck const& deck)
{
	return os << *deck.getDeck();
}