#include <iostream>
#include "Player.h"

Player::Player() : name("Anonymous"), hand(0), points(0), play(true)
{
	hand = new Hand<Card*>();
}

Player::Player(std::string name) : name(name), hand(0), points(0), play(true)
{
	hand = new Hand<Card*>();
}

Player::Player(Player const& copy) : name(copy.name), hand(0), points(copy.points), play(copy.play)
{
	hand = new Hand<Card*>(*(copy.hand));
}

Player::~Player() { delete hand; }

Player& Player::operator=(Player const& copy)
{
	if(this != &copy)
	{
		play = copy.play;
		name = copy.name;
		points = copy.points;
		delete hand;
		hand = new Hand<Card*>(*(copy.hand));
	}

	return *this;
}

void Player::setName(std::string name) { this -> name = name; }

void Player::setPlay(bool play) { this -> play = play; }

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
	std::cout << "Hand :" << std::endl;
	std::cout << *hand << std::endl;
}

int Player::getPoints() const { return points; }

Hand<Card*> *Player::getHand() const { return hand; }

bool Player::canPlay() const { return play; }

std::ostream& operator<<(std::ostream& os, Player const& player)
{
	os << "	- name : " << player.getName() << std::endl;
	os << "	- points : " << player.getPoints() << std::endl;
	os << "	- number of cards : " << player.getNumberOfCards() << std::endl;
	
	return os;
}
