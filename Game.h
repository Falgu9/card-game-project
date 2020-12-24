#ifndef __GAME__H__
#define __GAME__H__

#include "Player.h"
#include "Deck.h"

class Game
{
	friend std::ostream& operator<<(std::ostream& os, Game const& game);

protected:
	Deck *deck;
	Player **players;
	int numberOfPlayers;
	int turn;
	
public:
	Game();
	~Game();
	Game(Game const& copy);
	Game& operator=(Game const& copy);

	Deck *getDeck() const;
	Player **getPlayers() const;
	int getNumberOfPlayers() const;
	int getTurn() const;

	void incrementTurn();

	void distributeCards(int numberOfCardsToDeal);
};

#endif

