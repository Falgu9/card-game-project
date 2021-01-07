#ifndef __BELOTE__H__
#define __BELOTE__H__

#include "CardGame.h"
#include "Team.h"

class Belote : public CardGame
{
	friend std::ostream& operator<<(std::ostream& os, Belote const& belote);
private:
	Team **teams;
	Linkedlist<Card*> *playedCards;
	int indexTeamContract;
	int atout;
public:
	Belote();
	~Belote();

	void makeTeam();
	void setValueOfCards();
	void setValueOfCards(int rank, int suit, int value);
	void retourne();
	bool retourneHasBeenTaken();
	void play();
	void plis();
	void setPointsOfTeam(int indexPlis);
	void setNewOrderOfPlayers();
	void playCard();
	bool haveAtout();
	bool haveNonAtout();
	int getStrongerAtoutThanPlis();
	bool partenerIsMaster();
};

#endif