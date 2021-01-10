#ifndef __UNO__H__
#define __UNO__H__

#include "CardGame.h"

class Uno : public CardGame
{
	friend std::ostream& operator<<(std::ostream& os, Uno const& uno);
public:
	Uno();

	void play();
	void createUnoCards();
	Card *playIfPossible(Player *player);
	void cardPlusTwo();
	void cardPassTurn();
	Card *cardJoker(Player *player, int const& index);
	Card *cardPlusFour(Player *player, int const& index);
};

#endif