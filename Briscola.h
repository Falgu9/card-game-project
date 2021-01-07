#ifndef __BRISCOLA__H__
#define __BRISCOLA__H__

#include "CardGame.h"
#include "Team.h"

class Briscola : public CardGame
{
	friend std::ostream &operator<<(std::ostream &os, Briscola const &briscola);

private:
	Linkedlist<Card *> *playedCards;
	Card* briscolaCard;

public:
	Briscola();
	~Briscola();
	void setDeck();
	void play();
	void playCard();
	void setBricolaCard();
};

#endif
