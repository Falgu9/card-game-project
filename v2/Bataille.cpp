#include <thread>
#include <chrono>
#include "Bataille.h"

Bataille::Bataille()
{
	defaultDeck(1,false);
	setPlayers(2,2);

	setRandomOrder();
}

void Bataille::play()
{
	
	distributeCards(deck -> getDeckSize() / 2);

	Card *playedCardByPlayer1 = NULL;
	Card *playedCardByPlayer2 = NULL;

	while(true)
	{
		std::cout << "************************************\nTurn : " << turn << std::endl << std::endl;

		playedCardByPlayer1 = players[0] -> remove((players[0] -> getNumberOfCards()) - 1);
		playedCardByPlayer2 = players[1] -> remove((players[1] -> getNumberOfCards()) - 1);

		if(playedCardByPlayer1 != NULL && playedCardByPlayer2 != NULL) // both can play
		{
			std::cout << players[0] -> getName() << " play : " <<  *playedCardByPlayer1 << std::endl;
			std::cout << players[1] -> getName() << " play : " <<  *playedCardByPlayer2 << std::endl;

			if(*playedCardByPlayer1 > *playedCardByPlayer2)
			{
				players[0] -> addPoints((playedCardByPlayer1 -> getValue()) + (playedCardByPlayer2 -> getValue()));
				players[0] -> addCard(playedCardByPlayer1, 0);
				players[0] -> addCard(playedCardByPlayer2, 0);
			}

			if(*playedCardByPlayer1 < *playedCardByPlayer2)
			{
				players[1] -> addPoints((playedCardByPlayer1 -> getValue()) + (playedCardByPlayer2 -> getValue()));
				players[1] -> addCard(playedCardByPlayer1, 0);
				players[1] -> addCard(playedCardByPlayer2, 0);
			}

		}
		else if(playedCardByPlayer1 == NULL && playedCardByPlayer2 == NULL) // onone of players can play
		{
			std::cout << players[0] -> getName() << " play : Nothing" << std::endl;
			std::cout << players[1] -> getName() << " play : Nothing" << std::endl;
			std::cout << "Nobody won." << std::endl;
			return;
		}
		else if(playedCardByPlayer1 != NULL && playedCardByPlayer2 == NULL) // only one can play
		{
			std::cout << players[0] -> getName() << " play : " <<  *playedCardByPlayer1 << std::endl;
			std::cout << players[1] -> getName() << " play : Nothing" << std::endl;

			players[0] -> addPoints((playedCardByPlayer1 -> getValue()));
			std::cout << "Winner :\n" << *players[0] << std::endl;
			return;
		}
		else // none of players can play
		{
			std::cout << players[0] -> getName() << " play : Nothing" << std::endl;
			std::cout << players[1] -> getName() << " play : " <<  *playedCardByPlayer2 << std::endl;

			players[1] -> addPoints((playedCardByPlayer2 -> getValue()));
			std::cout << "Winner :\n" << *players[1] << std::endl;
			return;
		}

		std::cout << *this << std::endl;

		std::this_thread::sleep_for(std::chrono::milliseconds(1000));

		incrementTurn();
	}
}

std::ostream& operator<<(std::ostream& os, Bataille const& bataille)
{
	for(int i =0; i < bataille.numberOfPlayers; i++)
	{
		os << "Player " << i + 1 << " : " << std::endl;
		os << " - Name : " << bataille.players[i] -> getName() << std::endl;
		os << " - Number of cards : " << bataille.players[i] -> getNumberOfCards() << std::endl;
	}


	return os;
}