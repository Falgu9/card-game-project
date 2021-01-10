#include <thread>
#include <chrono>
#include "HuitAmericain.h"

HuitAmericain::HuitAmericain()
{
	
	setPlayers(2,5);
	setRandomOrder();
	
	int numberOfDeck = 0;
	while(true)
	{
		std::cout << "How many deck of 52 cards do you want?" << std::endl;
		std::cin >> numberOfDeck;
		if(numberOfDeck < 1)
			std::cout << "Error : must be at least 1 deck." << std::endl;
		else
			break;
	}
	
	defaultDeck(numberOfDeck, true);
	setValueOfCards();
	distributeCards(7);

	bool notSpecialCard = false;
	while(!notSpecialCard)
	{
		Card *card = deck -> deal();
		if(card -> getRank() == 7) {}
		else if(card -> getRank() == 13) {}
		else if(card -> getRank() == 10) {}
		else if(card -> getRank() == 0) {}
		else if(card -> getRank() == 1) {}
		else notSpecialCard = true;

		if(notSpecialCard)
			playedCard = card;
	}

	srand((unsigned int)time(NULL));

	int indexGifter = rand() % numberOfPlayers;
	swap(players[numberOfPlayers - 1], players[indexGifter]); // last player because gifter

	std::cout << "Order of players  : " << std::endl;
	std::cout << *this << std::endl;
}

void HuitAmericain::play()
{
	bool finished = false;
	while(!finished)
	{

		std::cout << "********************************Turn " << turn << "********************************" << std::endl;
		for(indexOfCurrentPlayer = 0; indexOfCurrentPlayer < numberOfPlayers; indexOfCurrentPlayer++)
		{
			std::cout << "last played card : " << "(value : " << playedCard -> getValue() << " ) " << *playedCard << std::endl;
			if(players[indexOfCurrentPlayer] -> canPlay())
			{
				players[indexOfCurrentPlayer] -> showHand();
				std::cout << "numer of cards : " << players[indexOfCurrentPlayer] -> getNumberOfCards() << std::endl;
				Card *currentPlayedCard = NULL;
				
				if((currentPlayedCard  = playIfPossible(players[indexOfCurrentPlayer])) != NULL)
				{
					playedCard = currentPlayedCard;
					std::cout << "Player " << indexOfCurrentPlayer+1 << " play " << "(value : " << playedCard -> getValue() << " ) " << *playedCard << std::endl;
					if(players[indexOfCurrentPlayer] -> getNumberOfCards() == 0)
					{
						std::cout << "Player : " << indexOfCurrentPlayer+1 << std::endl << *players[indexOfCurrentPlayer] << "\nWON\n";
						finished = true;
						break;
					}
				}
				else
				{
					std::cout << "player " << indexOfCurrentPlayer+1 << " pick." << std::endl;
					pick(players[indexOfCurrentPlayer], 1);
					players[indexOfCurrentPlayer] -> showHand();
					if((currentPlayedCard  = playIfPossible(players[indexOfCurrentPlayer])) != NULL)
					{
						playedCard = currentPlayedCard;
						std::cout << "Player " << indexOfCurrentPlayer+1 << " play " << "(value : " << playedCard -> getValue() << " ) " << *playedCard << std::endl;
					}
					else
						std::cout << "Player " << indexOfCurrentPlayer+1 << " can't play, pass turn." << std::endl;
				}
			}
			else
			{
				players[indexOfCurrentPlayer] -> setPlay(true);
				std::cout << "Player " << indexOfCurrentPlayer+1 << " can't play, pass turn." << std::endl;
			}

			std::cout << "-------------------------" << std::endl;
		}

		incrementTurn();
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	}
}

void HuitAmericain::setValueOfCard(int rank, int value)
{
	int size = deck -> getDeckSize();
	Card *tmp[size];

	for(int i = 0; i < size; i++)
	{
		tmp[i] = deck -> deal();
		if(tmp[i] -> getRank() == rank)
			tmp[i] -> setValue(value);
	}

	for(int i = size - 1; i >= 0; i--)
	{
		deck -> placeBack(tmp[i]);
	}
}

void HuitAmericain::setValueOfCards()
{
	setValueOfCard(8, 9); // 9
	setValueOfCard(6, 7); // 7
	setValueOfCard(5, 6); // 6
	setValueOfCard(4, 5); // 5
	setValueOfCard(3, 4); // 4
	setValueOfCard(2, 3); // 3
	setValueOfCard(12, 10); // King
	setValueOfCard(11, 10); // Queen
	setValueOfCard(10, 20); // Jack
	setValueOfCard(0, 20); // As
	setValueOfCard(1, 20); // 2
	setValueOfCard(7, 50); // 8
	setValueOfCard(13, 50); // Joker

	//not specified in rules
	setValueOfCard(9, 11); // 10
}

Card *HuitAmericain::playIfPossible(Player *player)
{
	for(int i = 0; i < player -> getNumberOfCards(); i++)
	{
		int rank = player -> getHand() -> getAtIndex(i) -> getRank();
		if(rank == 7) // 8 (change color)
			return cardEight(player, i);
		else if(rank == 13) // Joker (pick +4 to next player)
		{
			cardJoker();
			return player -> remove(i);
		}
		else if(rank == 10) // Jack (pass turn)
		{
			cardJack();
			return player -> remove(i);
		}
		else if(rank == 0) // Ace (change direction)
		{
			Card *card = player -> remove(i);
			changeDirection(player);
			return card;
		}
		else
		{
			if(rank == 1) // 2 (pick +2 to next player)
			{
				cardPlusTwo();
				return player -> remove(i);
			}
		}

		if(player -> getHand() -> getAtIndex(i) -> getSuit() == playedCard -> getSuit())
			return player -> remove(i);

		if(player -> getHand() -> getAtIndex(i) -> getValue() == playedCard -> getValue())
			return player -> remove(i);
	}

	return NULL;
}

Card *HuitAmericain::cardEight(Player *player, int const& index)
{
	int choosedColor;

	bool valid = false;
	while(!valid)
	{
		std::cout << "Choose a valid color : Spade = 1 / Heart = 2 / Club = 3 / Diamond = 4" << std::endl;
		std::cin >> choosedColor;
		if(choosedColor > 0 && choosedColor < 5)
			valid = true;
	}
	std::cout << "color was changed to : " << choosedColor << std::endl;

	Card *card = player -> remove(index);
	card -> setSuit(choosedColor - 1);

	return card;
}

void HuitAmericain::cardJoker()
{
	if(indexOfCurrentPlayer + 1 == numberOfPlayers)
		pick(players[0], 4);
	else
		pick(players[indexOfCurrentPlayer + 1], 4);
}

void HuitAmericain::cardJack()
{
	if(indexOfCurrentPlayer + 1 == numberOfPlayers)
		players[0] -> setPlay(false);
	else
		players[indexOfCurrentPlayer + 1] -> setPlay(false);
}

void HuitAmericain::cardPlusTwo()
{
	if(indexOfCurrentPlayer + 1 == numberOfPlayers)
		pick(players[0], 2);
	else
		pick(players[indexOfCurrentPlayer + 1], 2);
}

std::ostream& operator<<(std::ostream& os, HuitAmericain const& huitAmericain)
{
	for(int i = 0 ; i < huitAmericain.numberOfPlayers; i++)
	{
		os << "| " << huitAmericain.players[i] -> getName() << " , number of cards : " << huitAmericain.players[i] -> getNumberOfCards() << std::endl;
	}

	return os;
}