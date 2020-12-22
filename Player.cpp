#include "Player.h"
#include <iostream>

Player::Player() : name("Anonymous"), points(0), hand(0)
{
	hand = new Hand<Card*>();
}

Player::Player(std::string name) : name(name), points(0), hand(0)
{
	hand = new Hand<Card*>();
}

Player::Player(Player const& copy) : name(copy.name), points(copy.points), hand(0)
{
	hand = new Hand<Card*>(*(copy.hand));
}

Player::~Player()
{
	delete hand;
}

Player& Player::operator=(Player const& copy)
{
	if(this != &copy)
	{
		name = copy.name;
		points = copy.points;
		delete hand;
		hand = new Hand<Card*>(*(copy.hand));
	}

	return *this;
}

void Player::setName(std::string name) { this -> name = name; }

std::string Player::getName() const { return name; }

void Player::addCard(Card *card, int index)
{
	hand -> insertAtIndex(card, index);
}

void Player::addPoints(int points)
{
	this -> points += points;
}

Card *Player::remove(int index)
{
	return hand -> removeAtIndex(index);
}

Card *Player::remove(Card *card)
{
	return hand -> remove(card);
}

int Player::getNumberOfCards() const
{
	return hand -> getSize();
}

void Player::showHand() const
{
	std::cout << *hand << std::endl;
}

int Player::getPoints() const { return points; }

std::ostream& operator<<(std::ostream& os, const Player& player)
{
	return os << *(player.hand);
}
