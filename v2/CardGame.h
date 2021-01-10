#ifndef __CARDGAME__H__
#define __CARDGAME__H__

#include "Player.h"
#include "Deck.h"
#include <string>

class CardGame
{
	friend std::ostream &operator<<(std::ostream &os, CardGame const &CardGame);

protected:
	Deck *deck;
	Player **players;
	Card *playedCard;
	int indexOfCurrentPlayer;
	int numberOfPlayers;
	int turn;
	void swap(Player *player1, Player *player2);

public:
	CardGame();
	~CardGame();
	CardGame(CardGame const &copy);
	CardGame &operator=(CardGame const &copy);

	Deck *getDeck() const;
	Player **getPlayers() const;
	int getNumberOfPlayers() const;
	int getTurn() const;

	void setRandomOrder();
	void distributeCards(int numberOfCardsToDeal);
	void removeAllCardsOfPlayers();
	void pick(Player *player, int numberOfCardsToPick);
	void changeDirection(Player *player);
	void defaultDeck(int numberOfDeck, bool addJokers);
	void playWithDeckOf32(int numberOfDeck, bool addJokers);
	void incrementTurn();
	void setPlayers(int minPlayers,int maxPlayers);
};

#endif
