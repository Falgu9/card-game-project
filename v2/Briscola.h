#ifndef __BRISCOLA__H__
#define __BRISCOLA__H__

#include "CardGame.h"
#include "Team.h"
#include <vector>
#include <unistd.h>

class Briscola : public CardGame
{
	friend std::ostream &operator<<(std::ostream &os, Briscola const &briscola);

private:
	std::vector<Card *> playedCards;
	Card *briscolaCard;
	std::vector<int> turnScores;
	std::vector<int> roundScores;

	bool win;
	int winner;

public:
	Briscola();
	~Briscola();
	void setDeck();
	void play();
	void playCard();
	int evaluateScores(std::vector<int> scores);
	void printScores(std::vector<int> scores, std::string message);
	void winCheck();
};

#endif
