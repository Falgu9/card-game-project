#include "Belote.h"

Belote::Belote() : atout(-1), indexTeamContract(-1), playedCards(NULL)
{
	if (numberOfPlayers != 4)
	{
		std::cout << "Error : Must be 4 players." << std::endl;
		exit(1);
	}

	makeTeam();
	playWithDeckOf32(1, false);
	setValueOfCards();
	playedCards = new Linkedlist<Card *>();
	std::cout << "Order of players  : " << std::endl;
	std::cout << *this << std::endl;
}

Belote::~Belote()
{
	delete playedCards;
	delete teams[0];
	delete teams[1];
	delete[] teams;
}

void Belote::makeTeam()
{
	teams = new Team *[2];

	Team *team1 = new Team(2);
	team1->add(players[0]);
	team1->add(players[2]);

	Team *team2 = new Team(2);
	team2->add(players[1]);
	team2->add(players[3]);

	teams[0] = team1;
	teams[1] = team2;
}

void Belote::setValueOfCards()
{
	for (int i = 0; i < 4; i++)
	{
		if (i != atout)
		{
			setValueOfCards(0, i, 11); // As
			setValueOfCards(9, i, 10); // 10
			setValueOfCards(12, i, 4); // King
			setValueOfCards(11, i, 3); // Queen
			setValueOfCards(10, i, 2); // Jack
			setValueOfCards(8, i, 0);  // 9
			setValueOfCards(7, i, 0);  // 8
			setValueOfCards(6, i, 0);  // 7
		}
	}

	setValueOfCards(10, atout, 20); // Jack
	setValueOfCards(8, atout, 14);	// 9
}

void Belote::setValueOfCards(int rank, int suit, int value)
{
	int size = deck->getDeckSize();
	Card *tmp[size];
	for (int i = 0; i < size; i++)
	{
		tmp[i] = deck->deal();
		if (tmp[i]->getRank() == rank && tmp[i]->getSuit() == suit)
		{
			tmp[i]->setValue(value);
			size = i + 1;
			break;
		}
	}

	for (int i = 0; i < size; i++)
		deck->placeBack(tmp[i]);

	deck->shuffle();
}

/*
*
*	A FINIR
*	+
*	CORRIGER CERTAINS BUGS
*/

void Belote::play()
{
	retourne();

	int pli = 1;
	for (int i = 0; i < 8; i++)
	{
		std::cout << "******************* Plis " << pli << " *******************" << std::endl;
		plis();

		std::cout << "Player " << indexOfCurrentPlayer << " play " << *playedCard << std::endl;

		setPointsOfTeam(i);
		setNewOrderOfPlayers();
	}

	if (indexTeamContract == 0)
	{
		if (teams[0]->getPoints() < 82)
		{
			teams[0]->setPoints(0);
			teams[1]->addPoints(162);
		}
	}
	else
	{
		if (teams[1]->getPoints() < 82)
		{
			teams[1]->setPoints(0);
			teams[0]->addPoints(162);
		}
	}
}

void Belote::retourne()
{
	distributeCards(5);

	int turn = 0;
	while (true)
	{
		playedCard = deck->deal();
		std::cout << "retourne :\n"
				  << *playedCard << std::endl;
		if (turn % 2 == 0)
		{
			removeAllCardsOfPlayers();
			distributeCards(5);
		}
		for (int i = 0; i < numberOfPlayers; i++)
		{
			if (retourneHasBeenTaken())
			{
				if (i == 0 || i == 2)
					indexTeamContract = 0;
				else
					indexTeamContract = 1;

				distributeCards(3);
				players[i]->remove(0);
				players[i]->addCard(playedCard, 0);
				return;
			}
		}
		deck->placeBack(playedCard);
		deck->shuffle();
		turn++;
	}
}

bool Belote::retourneHasBeenTaken()
{
	players[indexOfCurrentPlayer]->showHand();

	int choice;
	while (true)
	{
		std::cout << "Do you want to take this card ? Yes = 0 / No = 1" << std::endl;
		std::cin >> choice;
		if (choice == 0)
		{
			atout = playedCard->getSuit();
			players[indexOfCurrentPlayer]->addCard(playedCard, 0);
			return true;
		}
		if (choice == 1)
			return false;
	}
}

void Belote::plis()
{
	for (indexOfCurrentPlayer = 0; indexOfCurrentPlayer < numberOfPlayers; indexOfCurrentPlayer++)
	{
		players[indexOfCurrentPlayer]->showHand();
		playCard();
	}
}

void Belote::setPointsOfTeam(int indexPlis)
{
	int points = 0;
	int indexMaxCard = 0;
	for (int i = 0; i < playedCards->getSize(); i++)
	{
		Card *tmp = playedCards->removeAtIndex(0);
		points += tmp->getValue();

		if (tmp->getValue() > playedCards->getAtIndex(indexMaxCard)->getValue())
			indexMaxCard = i;

		//belote et rebelote
		if ((tmp->getRank() == 12 && tmp->getSuit() == atout) || (tmp->getRank() == 11 && tmp->getSuit() == atout))
		{
			points += 20;
		}
	}

	if (indexMaxCard == 0 || indexMaxCard == 2)
	{
		teams[0]->addPoints(points);
		if (indexPlis == 7) // last plis
			teams[0]->addPoints(10);
	}
	else
	{
		teams[1]->addPoints(points);
		if (indexPlis == 7) // last plis
			teams[1]->addPoints(10);
	}
}

void Belote::setNewOrderOfPlayers()
{
	for (int i = 0; i < indexOfCurrentPlayer; i++)
	{
		swap(players[i + indexOfCurrentPlayer], players[i]);
	}
}

void Belote::playCard()
{
	int choice;

	if (indexOfCurrentPlayer == 0) // first player so can play any cards
	{
		std::cout << "You're the first player of the plis, you can play any cards of you want." << std::endl;
		while (true)
		{
			std::cout << "Choose a card of your hand. The index of this card must be between 1 and the number of cards you have." << std::endl;
			std::cin >> choice;
			if (choice > 0 && choice <= players[indexOfCurrentPlayer]->getNumberOfCards())
			{
				playedCard = players[indexOfCurrentPlayer]->remove(choice - 1);
				playedCards->insertAtIndex(playedCard, playedCards->getSize());
				return;
			}
		}
	}

	if (playedCard->getSuit() == atout) // last played card is an atout
	{
		if (partenerIsMaster()) // choose if he want to play
		{
			if (getStrongerAtoutThanPlis() != -1) // if can play with stronger atout
			{
				while (true)
				{
					std::cout << "You can play or not, do you want to play ? Yes = 0 / No = 1" << std::endl;
					std::cin >> choice;
					if (choice == 1)
						return;
					if (choice == 0)
						break;
				}

				while (true)
				{
					std::cout << "Choose an atout stronger than last played atout, index must be between 1 and number of cards." << std::endl;
					std::cin >> choice;
					if (choice > 0 && choice <= players[indexOfCurrentPlayer]->getNumberOfCards())
					{
						Card *tmp = players[indexOfCurrentPlayer]->remove(choice - 1);
						if (tmp->getValue() > playedCard->getValue())
						{
							playedCard = players[indexOfCurrentPlayer]->remove(choice - 1);
							playedCards->insertAtIndex(playedCard, playedCards->getSize());
							return;
						}
					}
				}
			}
		}
		else
		{
			if (getStrongerAtoutThanPlis() != -1)
			{
				while (true)
				{
					std::cout << "Choose an atout stronger than last played atout, index must be between 1 and number of cards." << std::endl;
					std::cin >> choice;
					if (choice > 0 && choice <= players[indexOfCurrentPlayer]->getNumberOfCards())
					{
						Card *tmp = players[indexOfCurrentPlayer]->remove(choice - 1);
						if (tmp->getValue() > playedCard->getValue())
						{
							playedCard = players[indexOfCurrentPlayer]->remove(choice - 1);
							playedCards->insertAtIndex(playedCard, playedCards->getSize());
							return;
						}
					}
				}
			}
			else
			{
				while (true)
				{
					std::cout << "Choose a card of your hand. The index of this card must be between 1 and the number of cards you have." << std::endl;
					std::cin >> choice;
					if (choice > 0 && choice <= players[indexOfCurrentPlayer]->getNumberOfCards())
					{
						playedCard = players[indexOfCurrentPlayer]->remove(choice - 1);
						playedCards->insertAtIndex(playedCard, playedCards->getSize());
						return;
					}
				}
			}
		}
	}
	else // last played card is a non atout
	{
		while (true)
		{
			std::cout << "Choose a card of your hand. The index of this card must be between 1 and the number of cards you have." << std::endl;
			std::cin >> choice;
			if (choice > 0 && choice <= players[indexOfCurrentPlayer]->getNumberOfCards())
			{
				playedCard = players[indexOfCurrentPlayer]->remove(choice - 1);
				playedCards->insertAtIndex(playedCard, playedCards->getSize());
				return;
			}
		}
	}
}

bool Belote::haveAtout()
{
	for (int i = 0; i < players[indexOfCurrentPlayer]->getNumberOfCards(); i++)
	{
		Card *tmp = players[indexOfCurrentPlayer]->remove(i);
		if (tmp->getSuit() == atout)
		{
			players[indexOfCurrentPlayer]->addCard(tmp, i);
			return true;
		}
	}

	return false;
}

bool Belote::haveNonAtout()
{
	if (players[indexOfCurrentPlayer]->getNumberOfCards() - haveAtout() > 0)
		return true;

	return false;
}

int Belote::getStrongerAtoutThanPlis()
{
	int indexmMaxValue = 0;
	for (int i = 0; i < playedCards->getSize(); i++)
	{
		if (playedCards->getAtIndex(i)->getValue() > playedCards->getAtIndex(indexmMaxValue)->getValue())
			indexmMaxValue = i;
	}

	for (int i = 0; i < players[indexOfCurrentPlayer]->getNumberOfCards(); i++)
	{
		Card *tmp = players[indexOfCurrentPlayer]->remove(i);
		if (tmp->getValue() > playedCards->getAtIndex(indexmMaxValue)->getValue())
		{
			players[indexOfCurrentPlayer]->addCard(tmp, i);
			return i;
		}
	}

	return -1;
}

bool Belote::partenerIsMaster()
{
	int maxValue = 0;
	for (int i = 0; i < playedCards->getSize(); i++)
	{
		if (playedCards->getAtIndex(i)->getValue() > playedCards->getAtIndex(maxValue)->getValue())
			maxValue = i;
	}

	if (maxValue == 0 && indexOfCurrentPlayer == 2 || maxValue == 1 && indexOfCurrentPlayer == 3)
	{
		return true;
	}

	return false;
}

std::ostream &operator<<(std::ostream &os, Belote const &belote)
{
	for (int i = 0; i < belote.numberOfPlayers; i++)
	{
		os << "| " << belote.players[i]->getName() << " , number of cards : " << belote.players[i]->getNumberOfCards() << std::endl;
	}

	return os;
}