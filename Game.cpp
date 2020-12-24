#include <iostream>
#include "Game.h"

Game::Game() : players(0), numberOfPlayers(0), deck(0), turn(0)
{
	deck = new Deck();
	deck -> shuffle();

	//system("clear");

	std::cout << "How many players ?" << std::endl;
	std::cin >> numberOfPlayers;

	players = new Player*[numberOfPlayers];

	for(int i = 1; i <= numberOfPlayers; i++)
	{
		std::string name;
		std::cout << "What's the name of player number " << i << " ?" << std::endl;
		std::cin >> name;
		players[i - 1] = new Player(name);
	}

	//system("clear");
}

Game::~Game()
{
	delete deck;

	for(int i = 0; i < numberOfPlayers; i++)
		delete players[i];

	delete[] players;
}

Game::Game(Game const& copy) : numberOfPlayers(copy.numberOfPlayers), deck(0), players(0)
{
	deck = new Deck(*(copy.deck));

	players = new Player*[numberOfPlayers];
	for(int i =0 ; i < numberOfPlayers; i++)
		players[i] = new Player(*(copy.players[i]));
}

Game& Game::operator=(Game const& copy)
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

Deck *Game::getDeck() const { return deck; }

Player **Game::getPlayers() const { return players; }

int Game::getNumberOfPlayers() const { return numberOfPlayers; }

int Game::getTurn() const { return turn; }

void Game::incrementTurn() { turn++; }

void Game::distributeCards(int numberOfCardsToDeal)
{
	if(numberOfCardsToDeal * numberOfPlayers > DECK_SIZE)
		std::cout << "Error : can't deal more than default deck size wich is " << DECK_SIZE << std::endl;
	
	for(int i = 0; i < numberOfCardsToDeal * numberOfPlayers; i++)
		players[i % numberOfPlayers] -> addCard(deck -> deal(), 0);
}

std::ostream& operator<<(std::ostream& os, Game const& game)
{
	os << game.turn << std::endl;

	for(int i =0; i < game.numberOfPlayers; i++)
		os << "Player " << i + 1 << " : " << std::endl << *game.players[i];

	return os;
}