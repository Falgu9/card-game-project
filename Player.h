#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include "Hand.h"
#include "Card.h"

class Player
{
	friend std::ostream &operator<<(std::ostream &os, Player const &player);

private:
	std::string name;
	Hand<Card *> *hand;
	int points;
	bool play;

public:
	Player();
	Player(std::string name);
	Player(Player const &copy);
	Player &operator=(Player const &copy);
	~Player();

	void setName(std::string name);
	void setPlay(bool play);

	void addCard(Card *card, int index);
	void addPoints(int points);
	Card *remove(int index);
	Card *remove(Card *card);

	int getPoints() const;
	Hand<Card *> *getHand() const;
	int getNumberOfCards() const;
	std::string getName() const;
	bool canPlay() const;

	void showHand() const;
};

#endif
