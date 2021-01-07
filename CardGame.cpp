#include <iostream>
#include <ctime>
#include "CardGame.h"

CardGame::CardGame() : players(0), numberOfPlayers(0), deck(0), turn(1), playedCard(NULL), indexOfCurrentPlayer(0)
{
	deck = new Deck();
	deck -> shuffle();

	std::cout << "How many players ?" << std::endl;
	std::cin >> numberOfPlayers;

	players = new Player*[numberOfPlayers];

	for(int i = 0; i < numberOfPlayers; i++)
	{
		std::string name;
		std::cout << "What's the name of player number " << i + 1 << " ?" << std::endl;
		std::cin >> name;

		while(true)
		{
			bool notOk = false;
			if(i == 0)
			{
				break;
			}
			else
				for(int j = 0; j < i; j++)
					if(players[j] -> getName() == name)
						notOk = true;
			if(notOk)
			{
				std::cout << "Name already exist, choose an other." << std::endl;
				std::cin >> name;
			}
			else
				break;
		}

		players[i] = new Player(name);
	}

	setRandomOrder();
}

CardGame::~CardGame()
{
	delete deck;

	for(int i = 0; i < numberOfPlayers; i++)
		delete players[i];

	delete[] players;
}

CardGame::CardGame(CardGame const& copy) : numberOfPlayers(copy.numberOfPlayers), deck(0), players(0)
{
	deck = new Deck(*(copy.deck));

	players = new Player*[numberOfPlayers];
	for(int i =0 ; i < numberOfPlayers; i++)
		players[i] = new Player(*(copy.players[i]));
}

CardGame& CardGame::operator=(CardGame const& copy)
{
	if(this != &copy)
	{
		numberOfPlayers = copy.numberOfPlayers;
		
		delete deck;

		for(int i =0; i < numberOfPlayers; i++)
			delete players[i];

		delete[] players;

		deck = new Deck(*(copy.deck));

		players = new Player*[numberOfPlayers];
		for(int i =0 ; i < numberOfPlayers; i++)
			players[i] = new Player(*(copy.players[i]));
	}

	return *this;
}

void CardGame::swap(Player *player1, Player *player2)
{
	Player tmp = *player1;
	*player1 = *player2;
	*player2 = tmp;
}

void CardGame::setRandomOrder()
{
	srand((unsigned int)time(NULL));

	for(int i = 0; i < 500; i++)
	{
		swap(players[rand() % numberOfPlayers], players[rand() % numberOfPlayers]);
	}
}

Deck *CardGame::getDeck() const { return deck; }

Player **CardGame::getPlayers() const { return players; }

int CardGame::getNumberOfPlayers() const { return numberOfPlayers; }

int CardGame::getTurn() const { return turn; }

void CardGame::incrementTurn() { turn++; }

void CardGame::pick(Player *player, int numberOfCardsToPick)
{
	for(int i = 0; i < numberOfCardsToPick; i++)
		player -> addCard(deck -> deal(), 0);
}

void CardGame::playWithDeckOf32(int numberOfDeck, bool addJokers)
{
	delete deck;

	deck = new Deck(32, numberOfDeck, addJokers);
	deck -> shuffle();
}

void CardGame::defaultDeck(int numberOfDeck, bool addJokers)
{
	delete deck;

	deck = new Deck(52, numberOfDeck, addJokers);
	deck -> shuffle();
}

void CardGame::distributeCards(int numberOfCardsToDeal)
{
	if(numberOfCardsToDeal * numberOfPlayers > deck -> getDeckSize())
	{
		std::cout << "Error : can't deal more than default deck size wich is " << deck -> getDeckSize() << std::endl;
		exit(1);
	}
	
	for(int i = 0; i < numberOfCardsToDeal * numberOfPlayers; i++)
		players[i % numberOfPlayers] -> addCard(deck -> deal(), 0);
}

void CardGame::changeDirection(Player *player)
{
	std::string name = player -> getName();

	for(int i = 0; i < numberOfPlayers / 2; i++)
		swap(players[i], players[numberOfPlayers - i - 1]);

	for(int i = 0; i < numberOfPlayers; i++)
	{
		if(players[i] -> getName() ==  name)
		{
			indexOfCurrentPlayer = i;
			break;
		}
	}

	for(int i = 0; i < numberOfPlayers; i++)
		std::cout << "new order :\n" << "player " << i+1 << " is " << players[i] -> getName() << std::endl;

	std::cout << "current player is : " << players[indexOfCurrentPlayer] -> getName() << std::endl;
}

void CardGame::removeAllCardsOfPlayers()
{
	for(int i = 0; i < numberOfPlayers; i++)
		for(int j =0; j < players[i] -> getNumberOfCards(); j++)
			deck -> placeBack(players[i] -> remove(0));

	deck -> shuffle();
}

std::ostream& operator<<(std::ostream& os, CardGame const& CardGame)
{
	os << CardGame.turn << std::endl;

	for(int i =0; i < CardGame.numberOfPlayers; i++)
		os << "Player " << i + 1 << " : " << std::endl << *CardGame.players[i];

	return os;
}