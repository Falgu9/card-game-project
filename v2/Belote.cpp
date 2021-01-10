#include "Belote.h"

Belote::Belote() : playedCards(NULL), indexTeamContract(-1),atout(-1)
{
	setPlayers(4,4);

	makeTeam();
	playWithDeckOf32(1, false);
	setValueOfCards();
	playedCards = new Linkedlist<Card*>();
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
	teams = new Team*[2];

	Team *team1 = new Team(2);
	team1 -> add(players[0]);
	team1 -> add(players[2]);

	Team *team2 = new Team(2);
	team2 -> add(players[1]);
	team2 -> add(players[3]);

	teams[0] = team1;
	teams[1] = team2;
}

void Belote::setValueOfCards()
{
	for(int i = 0; i < 4; i++)
	{
		if(i != atout)
		{
			setValueOfCards(0, i, 11); // As
			setValueOfCards(9, i, 10); // 10
			setValueOfCards(12, i, 4); // King
			setValueOfCards(11, i, 3); // Queen
			setValueOfCards(10, i, 2); // Jack
			setValueOfCards(8, i, 0); // 9
			setValueOfCards(7, i, 0); // 8
			setValueOfCards(6, i, 0); // 7
		}
	}

	setValueOfCards(10, atout, 20); // Jack
	setValueOfCards(8, atout, 14); // 9
}

void Belote::setValueOfCards(int rank, int suit, int value)
{
	int size = deck -> getDeckSize();
	Card* tmp[size];
	for (int i = 0; i < size; i++)
	{
		tmp[i] = deck -> deal();
		if(tmp[i] -> getRank() == rank && tmp[i] -> getSuit() == suit)
		{
			tmp[i] -> setValue(value);
			size = i + 1;
			break;
		}
	}

	for(int i = 0; i < size; i++)
		deck -> placeBack(tmp[i]);

	deck -> shuffle();
}

void Belote::play()
{
	retourne();

	int pli = 1;
	for(int i = 0; i < 8; i ++)
	{
		std::cout << "******************* Plis " << pli << " *******************" << std::endl;

		plis();
		setPointsOfTeam(i);
		//setNewOrderOfPlayers();

		pli++;
	}

	if(indexTeamContract == 0)
	{
		if(teams[0] -> getPoints() < 82)
		{
			teams[0] -> setPoints(0);
			teams[1] -> addPoints(162);
		}
	}
	else
	{
		if(teams[1] -> getPoints() < 82)
		{
			teams[1] -> setPoints(0);
			teams[0] -> addPoints(162);
		}
	}

	if(teams[0] -> getPoints() > teams[1] -> getPoints())
		std::cout << "winner of the game is team 1 : \n" << *teams[0] << std::endl;
	else
		std::cout << "winner of the game is team 2 : \n" << *teams[1] << std::endl;
}

void Belote::retourne()
{
	distributeCards(5);

	int turn = 0;
	while(true)
	{
		Card *retourne = deck -> deal();
		if(turn != 0 && turn % 2 == 0)
		{
			removeAllCardsOfPlayers();
			distributeCards(5);
		}
		for(int i = 0; i < numberOfPlayers; i++)
		{
			indexOfCurrentPlayer = i;
			players[indexOfCurrentPlayer] -> showHand();
			std::cout << "retourne : " << *retourne << std::endl;
			if(retourneHasBeenTaken(retourne))
				return;
		}
		deck -> placeBack(retourne);
		deck -> shuffle();
		turn++;
	}
}

bool Belote::retourneHasBeenTaken(Card *retourne)
{
	int choice;
	while(true)
	{
		std::cout << "Do you want to take this retourne ? Yes = 0 / No = 1" << std::endl;
		std::cin >> choice;
		if(choice == 0)
		{
			atout = retourne -> getSuit();
			players[indexOfCurrentPlayer] -> addCard(retourne, 0);

			if(indexOfCurrentPlayer == 0 || indexOfCurrentPlayer == 2)
				indexTeamContract = 0;
			else
				indexTeamContract = 1;

			for(int i = 0; i < numberOfPlayers; i++)
				if(i == indexOfCurrentPlayer)
				{
					players[i] -> addCard(deck -> deal(), 0);
					players[i] -> addCard(deck -> deal(), 0);
				}
				else
				{
					players[i] -> addCard(deck -> deal(), 0);
					players[i] -> addCard(deck -> deal(), 0);
					players[i] -> addCard(deck -> deal(), 0);
				}

			return true;
		}
		if(choice == 1)
			return false;
	}
}

void Belote::plis()
{
	for(indexOfCurrentPlayer = 0; indexOfCurrentPlayer < numberOfPlayers; indexOfCurrentPlayer++)
	{
		std::cout << "-------------------Player " << indexOfCurrentPlayer << "-------------------" << std::endl;
		std::cout << "atout is : " << atout << " (suit = " << atout << ")" << std::endl;
		if(playedCard == NULL)
			std::cout << "last played card : none" << std::endl;
		else
			std::cout << "last played card : " << *playedCard << std::endl;
		
		players[indexOfCurrentPlayer] -> showHand();
		playCard();

		std::cout << "Player " << indexOfCurrentPlayer << " play " << *playedCard << std::endl;
	}
}

void Belote::setPointsOfTeam(int indexPlis)
{
	int points = 0;
	int indexMaxCard = 0;
	int size = playedCards -> getSize();
	for(int i = 0; i < size; i++)
	{
		//Card *tmp = playedCards -> removeAtIndex(0);
		points += playedCards -> getAtIndex(i) -> getValue();
		if(playedCards -> getAtIndex(i) -> getValue() > playedCards -> getAtIndex(indexMaxCard) -> getValue())
			indexMaxCard = i;
		//belote et rebelote
		if((playedCards -> getAtIndex(i) -> getRank() == 12 && playedCards -> getAtIndex(i) -> getSuit() == atout) || (playedCards -> getAtIndex(i) -> getRank() == 11 && playedCards -> getAtIndex(i) -> getSuit() == atout))
		{
			points += 20;
		}
	}

	for(int i = 0; i < size; i++)
	{
		playedCards -> removeAtIndex(0);
	}

	if(indexMaxCard == 0 || indexMaxCard == 2)
	{
		teams[0] -> addPoints(points);
		if(indexPlis == 7) // last plis
			teams[0] -> addPoints(10);

		std::cout << "winner of the plis is team 1 : " << std::endl;
		std::cout << *teams[0] << std::endl;
	}
	else
	{
		teams[1] -> addPoints(points);
		if(indexPlis == 7) // last plis
			teams[1] -> addPoints(10);

		std::cout << "winner of the plis is team 2 : " << std::endl;
		std::cout << *teams[0] << std::endl;
	}
}

void Belote::setNewOrderOfPlayers()
{
	for(int i = 0; i < indexOfCurrentPlayer; i++)
	{
		swap(players[i + indexOfCurrentPlayer], players[i]);
	}
}

void Belote::playCard()
{
	
	if(indexOfCurrentPlayer == 0) // first player so can play any cards
	{
		std::cout << "You're the first player of the plis." << std::endl;
		playAnyCard();
		return;
	}

	if(playedCard -> getSuit() == atout) // last played card is an atout
	{
		if(haveStrongerAtout())
		{
			int choice;
			while(true)
			{
				std::cout << "You must play an stronger atout. Choose a card of your hand. The index of this card must be between 1 and the number of cards you have." << std::endl;
				std::cin >> choice;
				if(choice > 0 && choice <= players[indexOfCurrentPlayer] -> getNumberOfCards())
				{
					Card *tmp = players[indexOfCurrentPlayer] -> remove(choice - 1);
					if(tmp -> getValue() > playedCard -> getValue() && tmp -> getSuit() == atout)
					{
						playedCard = tmp;
						playedCards -> insertAtIndex(tmp, playedCards -> getSize());
						return;
					}
					players[indexOfCurrentPlayer] -> addCard(tmp, choice - 1);
				}
			}
		}

		playAnyCard();
		return;
	}
	else
	{
		if(canPlayNonAtout())
		{
			int choice;
			while(true)
			{
				std::cout << "You can play non atout. Choose a card of your hand. The index of this card must be between 1 and the number of cards you have." << std::endl;
				std::cin >> choice;
				if(choice > 0 && choice <= players[indexOfCurrentPlayer] -> getNumberOfCards())
				{
					Card *tmp = players[indexOfCurrentPlayer] -> remove(choice - 1);
					if(tmp -> getSuit() == playedCard -> getSuit())
					{
						playedCard = tmp;
						playedCards -> insertAtIndex(tmp, playedCards -> getSize());
						return;
					}
					players[indexOfCurrentPlayer] -> addCard(tmp, choice - 1);
				}
			}
		}
		if(partenerIsMaster() && haveNoAtout())
		{
			playAnyCard();
			return;
		}
		if(haveNoAtout())
		{
			playAnyCard();
			return;
		}

		playAtout();
	}
}

bool Belote::canPlayNonAtout()
{
	for(int i = 0; i < players[indexOfCurrentPlayer] -> getNumberOfCards(); i++)
	{
		Card *tmp = players[indexOfCurrentPlayer] -> remove(i);
		if(tmp -> getSuit() == playedCard -> getSuit())
		{
			players[indexOfCurrentPlayer] -> addCard(tmp, i);
			return true;
		}
		players[indexOfCurrentPlayer] -> addCard(tmp, i);
	}

	return false;
}

bool Belote::haveStrongerAtout()
{
	for(int i = 0; i < players[indexOfCurrentPlayer] -> getNumberOfCards(); i++)
	{
		Card *tmp = players[indexOfCurrentPlayer] -> remove(i);
		if(tmp -> getValue() > playedCard -> getValue() && tmp -> getSuit() == atout)
		{
			players[indexOfCurrentPlayer] -> addCard(tmp, i);
			return true;
		}
		players[indexOfCurrentPlayer] -> addCard(tmp, i);
	}

	return false;
}

void Belote::playAnyCard()
{
	int choice;
	while(true)
	{
		std::cout << "You can play any card. Choose a card of your hand. The index of this card must be between 1 and the number of cards you have." << std::endl;
		std::cin >> choice;
		if(choice > 0 && choice <= players[indexOfCurrentPlayer] -> getNumberOfCards())
		{
			playedCard = players[indexOfCurrentPlayer] -> remove(choice - 1);
			playedCards -> insertAtIndex(playedCard, playedCards -> getSize());
			return;
		}
	}
}

bool Belote::playNonAtout()
{
	bool canPlay = false;
	for(int i = 0; i < players[indexOfCurrentPlayer] -> getNumberOfCards(); i++)
	{
		Card *tmp = players[indexOfCurrentPlayer] -> remove(i);
		if(tmp -> getSuit() == playedCard -> getSuit())
			canPlay = true;
		players[indexOfCurrentPlayer] -> addCard(tmp, i);
	}

	int choice;
	if(canPlay)
		while(true)
		{
			std::cout << "You can play a non atout. Choose a card of your hand. The index of this card must be between 1 and the number of cards you have." << std::endl;
			std::cin >> choice;
			if(choice > 0 && choice <= players[indexOfCurrentPlayer] -> getNumberOfCards())
			{
				Card *tmp = players[indexOfCurrentPlayer] -> remove(choice - 1);
				if(tmp -> getSuit() == playedCard -> getSuit())
				{
					playedCard = tmp;
					playedCards -> insertAtIndex(playedCard, playedCards -> getSize());
					return true;
				}
				players[indexOfCurrentPlayer] -> addCard(tmp, choice - 1);
			}
		}

	return false;
}

void Belote::playAtout()
{
	int choice;
	while(true)
	{
		std::cout << "You must play an atout. Choose a card of your hand. The index of this card must be between 1 and the number of cards you have." << std::endl;
		std::cin >> choice;
		if(choice > 0 && choice <= players[indexOfCurrentPlayer] -> getNumberOfCards())
		{
			Card *tmp = players[indexOfCurrentPlayer] -> remove(choice -1);
			if(tmp -> getSuit() == atout)
			{
				playedCard = tmp;
				playedCards -> insertAtIndex(playedCard, playedCards -> getSize());
				return;
			}
			players[indexOfCurrentPlayer] -> addCard(tmp, choice - 1);
		}
	}
}

bool Belote::haveNoAtout()
{
	for(int i = 0; i < players[indexOfCurrentPlayer] -> getNumberOfCards(); i++)
	{
		Card *tmp = players[indexOfCurrentPlayer] -> remove(i);
		if(tmp -> getSuit() == atout)
		{
			players[indexOfCurrentPlayer] -> addCard(tmp, i);
			return false;
		}
		players[indexOfCurrentPlayer] -> addCard(tmp, i);
	}

	return true;
}

bool Belote::partenerIsMaster()
{
	int maxValue = 0;
	for(int i = 0; i < playedCards -> getSize(); i++)
	{
		if(playedCards -> getAtIndex(i) -> getValue() > playedCards -> getAtIndex(maxValue) -> getValue())
			maxValue = i;
	}

	if((maxValue == 0 && indexOfCurrentPlayer == 2) || (maxValue == 1 && indexOfCurrentPlayer == 3))
	{
		return true;
	}

	return false;
}

std::ostream& operator<<(std::ostream& os, Belote const& belote)
{
	for(int i = 0 ; i < belote.numberOfPlayers; i++)
	{
		os << "| " << belote.players[i] -> getName() << " , number of cards : " << belote.players[i] -> getNumberOfCards() << std::endl;
	}

	return os;
}