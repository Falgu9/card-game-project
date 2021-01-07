#include <ctime>
#include <cstdlib>
#include "Deck.h"

Deck::Deck() : deck(0), deckSize(52)
{
	deck = new Stack<Card*>(deckSize);

	for(int i = 0; i < 4; i++)
		for(int j = 0; j < 13; j++)
		{
			if(j == 0)
				deck -> push(new Card(j, i, 14));
			else
				deck -> push(new Card(j, i, j + 1));
		}
}

Deck::Deck(int capacity) : deck(0), deckSize(0)
{
	deck = new Stack<Card*>(capacity);
}

Deck::Deck(int defaultDeckSize, int numberOfDeck, bool jokers) : deck(0), deckSize(defaultDeckSize * numberOfDeck)
{
	if(numberOfDeck <= 0)
	{
		std::cout << "Error : must add at least one deck." << std::endl;
		exit(1);
	}

	if(defaultDeckSize != 32 && defaultDeckSize != 52)
	{
		std::cout << "Error : default deck size must be 32 or 52." << std::endl;
		exit(1);
	}

	if(jokers)
	{
		deckSize += 2;
		deck = new Stack<Card*>(deckSize);
		deck -> push(new Card(13, -1));
		deck -> push(new Card(13, -1));
	}
	else
	{
		deck = new Stack<Card*>(deckSize);
	}

	if(defaultDeckSize == 52)
		for(int a = 0; a < numberOfDeck; a++)
			for(int i = 0; i < 4; i++)
				for(int j = 0; j < 13; j++)
				{
					if(j == 0)
						deck -> push(new Card(j, i, 14));
					else
						deck -> push(new Card(j, i, j + 1));
				}
	else
		for(int a = 0; a < numberOfDeck; a++)
			for(int i = 0; i < 4; i++)
				for(int j = 0; j < 13; j++)
				{
					if(j < 1 || j > 5)
					{
						if(j == 0)
							deck -> push(new Card(j, i, 14));
						else
							deck -> push(new Card(j, i, j + 1));
					}
				}
}

Deck::~Deck()
{
	delete deck;
}

Deck::Deck(Deck const& copy) { deck = new Stack<Card*>(*(copy.deck)); }

Deck& Deck::operator=(Deck const& copy)
{
	if(this != &copy)
	{
		delete deck;
		deck = new Stack<Card*>(*(copy.deck));
	}

	return *this;
}

Card* Deck::deal() {
	deckSize--;
	return deck -> pop();
}

Deck* Deck::placeBack(Card *card)
{
	deckSize++;
	deck -> push(card);
	return this;
}

Deck* Deck::shuffle()
{
	int size = deckSize;
	Card* tmp[size];
	for (int i = 0; i < size; i++)
		tmp[i] = deck -> pop();

	srand((unsigned int)time(NULL));

	for (int i = 0; i < 500; i++)
		swap(tmp[rand() % size], tmp[rand() % size]);

	for (int i = 0; i < size; i++)
		deck -> push(tmp[i]);

	return this;
}

void Deck::swap(Card *card1, Card *card2)
{
	Card tmp = *card1;
	*card1 = *card2;
	*card2 = tmp;
}

Stack<Card*> *Deck::getDeck() const { return deck; }


void Deck::setDeckSize(int deckSize) { this -> deckSize = deckSize; }

int Deck::getDeckSize() const { return deckSize; }

std::ostream& operator<<(std::ostream& os, Deck const& deck)
{
	return os << *deck.getDeck();
}