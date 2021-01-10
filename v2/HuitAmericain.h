#ifndef __HUIT_AMERICAIN__H__
#define __HUIT_AMERICAIN__H__

#include "CardGame.h"

class HuitAmericain : public CardGame
{
	friend std::ostream& operator<<(std::ostream& os, HuitAmericain const& huitAmericain);
private:
	Card *playedCard;
	int indexOfCurrentPlayer;
public:
	HuitAmericain();
	void play();
	void setValueOfCard(int rank, int value);
	void setValueOfCards();
	void changeDirectionOfGame(Player *player);
	Card *playIfPossible(Player *player);
	Card *cardEight(Player *player, int const& index);
	void cardJoker();
	void cardJack();
	void cardPlusTwo();
};

#endif

