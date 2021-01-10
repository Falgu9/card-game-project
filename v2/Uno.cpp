#include "Uno.h"
#include <thread>
#include <chrono>

Uno::Uno()
{
	setPlayers(2,-1);

	setRandomOrder();
	
	createUnoCards();
	distributeCards(7);

	//gifter play the dealed card
	playedCard  = deck -> deal();
	Player *gifter = new Player("gifter");
	int index = 0;
	gifter -> addCard(playedCard, 0);
	if(playedCard -> getRank() == 11) // "Change direction"
		changeDirection(gifter);
	if(playedCard -> getRank() == 12) // Pass turn
		cardPassTurn();
	if(playedCard -> getRank() == 10) // +2
		cardPlusTwo();
	if(playedCard -> getRank() == 13) // Joker
		cardJoker(gifter, index);
	if(playedCard -> getRank() == 14)
		cardPlusFour(gifter, index);
	delete gifter;

	std::cout << "Order of players  : " << std::endl;
	std::cout << *this << std::endl;
}

void Uno::createUnoCards()
{
	// 4 card 0
	for(int i = 0; i < 4; i++)
		deck -> placeBack(new Card(0, i,"<<0>>"));

	// 18 cards 1 to 9 for each color
	for(int a = 0; a < 2; a++)
		for(int i = 1; i < 10; i++)
		{
			deck -> placeBack(new Card(i, 0, "<<" + std::to_string(i) + ">>"));
			deck -> placeBack(new Card(i, 1, "<<" + std::to_string(i) + ">>"));
			deck -> placeBack(new Card(i, 2, "<<" + std::to_string(i) + ">>"));
			deck -> placeBack(new Card(i, 3, "<<" + std::to_string(i) + ">>"));

		}

	for(int a = 0; a < 2; a++)
	{
		// card +2
		deck -> placeBack(new Card(10, 0, "<<+2>>"));
		deck -> placeBack(new Card(10, 1, "<<+2>>"));
		deck -> placeBack(new Card(10, 2, "<<+2>>"));
		deck -> placeBack(new Card(10, 3, "<<+2>>"));

		// 8 cards <<change direction>>
		deck -> placeBack(new Card(11, 0, "<<change direction>>"));
		deck -> placeBack(new Card(11, 1, "<<change direction>>"));
		deck -> placeBack(new Card(11, 2, "<<change direction>>"));
		deck -> placeBack(new Card(11, 3, "<<change direction>>"));

		// 8 cards pass turn
		deck -> placeBack(new Card(12, 0, "<<pass turn>>"));
		deck -> placeBack(new Card(12, 1, "<<pass turn>>"));
		deck -> placeBack(new Card(12, 2, "<<pass turn>>"));
		deck -> placeBack(new Card(12, 3, "<<pass turn>>"));
	}

	// 4 Joker
	deck -> placeBack(new Card(13, -1, "<<Joker>>"));
	deck -> placeBack(new Card(13, -1, "<<Joker>>"));
	deck -> placeBack(new Card(13, -1, "<<Joker>>"));
	deck -> placeBack(new Card(13, -1, "<<Joker>>"));

	// 4 cards +4
	deck -> placeBack(new Card(14, -1, "<<+4>>"));
	deck -> placeBack(new Card(14, -1, "<<+4>>"));
	deck -> placeBack(new Card(14, -1, "<<+4>>"));
	deck -> placeBack(new Card(14, -1, "<<+4>>"));

	deck -> shuffle();
}

void Uno::play()
{
	bool finished = false;
	while(!finished)
	{

		std::cout << "********************************Turn " << turn << "********************************" << std::endl;
		for(indexOfCurrentPlayer = 0; indexOfCurrentPlayer < numberOfPlayers; indexOfCurrentPlayer++)
		{
			std::cout << "last played card : " << *playedCard << std::endl;
			if(players[indexOfCurrentPlayer] -> canPlay())
			{
				players[indexOfCurrentPlayer] -> showHand();
				std::cout << "numer of cards : " << players[indexOfCurrentPlayer] -> getNumberOfCards() << std::endl;
				Card *currentPlayedCard = NULL;
				
				if((currentPlayedCard  = playIfPossible(players[indexOfCurrentPlayer])) != NULL)
				{
					playedCard = currentPlayedCard;
					std::cout << "Player " << indexOfCurrentPlayer+1 << " play : " << *playedCard << std::endl;
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
						std::cout << "Player " << indexOfCurrentPlayer+1 << " play : " << *playedCard << std::endl;
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
			if(indexOfCurrentPlayer != numberOfPlayers - 1)
				std::cout << "-------------------------" << std::endl;
		}

		incrementTurn();
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	}
}

Card *Uno::playIfPossible(Player *player)
{
	int indexPlusfour = -1;
	int indexJoker = -1;
	for(int i = 0; i < player -> getNumberOfCards(); i++)
	{
		int rank = player -> getHand() -> getAtIndex(i) -> getRank();
		int suit = player -> getHand() -> getAtIndex(i) -> getSuit();
		std::string symbol = player -> getHand() -> getAtIndex(i) -> getSymbol();

		if(suit == playedCard -> getSuit() || rank == playedCard -> getRank() || symbol == playedCard -> getSymbol())
		{
			if(rank == 12) // Pass turn
			{
				cardPassTurn();
				return player -> remove(i);
			}
			if(rank == 10) // +2
			{
				cardPlusTwo();
				return player -> remove(i);
			}

			return player -> remove(i);
		}

		if(rank == 11) // "Change direction"
		{
			Card *card = player -> remove(i);
			changeDirection(player);
			return card;
		}

		if(rank == 13) // Joker
			indexJoker = i;
		//last choice (card +4)
		if(rank == 14)
			indexPlusfour = i;
	}

	if(indexJoker != -1)
		return cardJoker(player, indexJoker);

	if(indexPlusfour != -1)
		return cardPlusFour(player, indexPlusfour);

	return NULL;
}

void Uno::cardPlusTwo()
{
	if(indexOfCurrentPlayer + 1 == numberOfPlayers)
	{
		pick(players[0], 2);
		players[0] -> setPlay(false);
	}
	else
	{
		pick(players[indexOfCurrentPlayer + 1], 2);
		players[indexOfCurrentPlayer + 1] -> setPlay(false);
	}
}

void Uno::cardPassTurn()
{
	if(indexOfCurrentPlayer + 1 == numberOfPlayers)
		players[0] -> setPlay(false);
	else
		players[indexOfCurrentPlayer + 1] -> setPlay(false);
}

Card *Uno::cardJoker(Player *player, int const& index)
{
	int choosedColor;

	bool valid = false;
	while(!valid)
	{
		std::cout << "Choose a valid color : suit 0 (Red) = 1 / suit 1 (Green) = 2 / suit 2 (Blue) = 3 / suit 3 (Yellow) = 4" << std::endl;
		std::cin >> choosedColor;
		if(choosedColor > 0 && choosedColor < 5)
			valid = true;
	}
	std::cout << "color was changed to : " << choosedColor << std::endl;

	Card *card = player -> remove(index);
	card -> setSuit(choosedColor - 1);

	return card;
}

Card *Uno::cardPlusFour(Player *player,  int const& index)
{
	if(indexOfCurrentPlayer + 1 == numberOfPlayers)
	{
		pick(players[0], 4);
		players[0] -> setPlay(false);
	}
	else
	{
		pick(players[indexOfCurrentPlayer + 1], 4);
		players[indexOfCurrentPlayer + 1] -> setPlay(false);
	}

	int choose;
	std::cout << "Do you want to change color ? No = 0 / Yes = 1" << std::endl;
	std::cin >> choose;
	Card *card = NULL;
	while(true)
	{
		if(choose == 1)
		{
			card = cardJoker(player, index);
			break;
		}
		if(choose == 0)
			break;
	}

	if(card == NULL)
		return player -> remove(index);

	return card;
}

std::ostream& operator<<(std::ostream& os, Uno const& uno)
{
	for(int i = 0 ; i < uno.numberOfPlayers; i++)
	{
		os << "| " << uno.players[i] -> getName() << " , number of cards : " << uno.players[i] -> getNumberOfCards() << std::endl;
	}

	return os;
}