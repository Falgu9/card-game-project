#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include "Hand.h"
#include "Card.h"

class Player
{
	friend std::ostream& operator<<(std::ostream& os, const Player& player);

private:
	std::string name;
	Hand<Card*> *hand;
	int points;

public:
	Player();
	Player(std::string name);
	Player(Player const& copy);
	Player& operator=(Player const& copy);
	~Player();
			
	void setName(std::string name);
	std::string getName() const;

	void addCard(Card *card, int index);
	void addPoints(int points);
	Card *remove(int index);
	Card *remove(Card *card);

	int getPoints() const;
	int getNumberOfCards() const;

	void showHand() const;


};

#endif
