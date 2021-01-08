#include <chrono>
#include "Briscola.h"

Briscola::Briscola() : win(false), winner(0)
{
	//faire une fonction resetplayer, changements de jeu
	if (numberOfPlayers != 2)
	{
		std::cout << "Error : Must be 2 players." << std::endl;
		exit(1);
	}

	playedCards = std::vector<Card *>();
	briscolaCard = new Card();
	turnScores = std::vector<int>(), roundScores = std::vector<int>(numberOfPlayers);

	setDeck();
}

void Briscola::setDeck()
{
	for (int i = 0; i < 4; i++)
	{
		deck->placeBack(new Card(13, i, 11, "As"));		 // A
		deck->placeBack(new Card(12, i, 4, "Roi"));		 // King
		deck->placeBack(new Card(11, i, 3, "Reine"));	 // Queen
		deck->placeBack(new Card(10, i, 2, "Cavalier")); // Jack
		deck->placeBack(new Card(6, i, 0, "7"));		 // 7
		deck->placeBack(new Card(5, i, 0, "6"));		 // 6
		deck->placeBack(new Card(4, i, 0, "5"));		 // 5
		deck->placeBack(new Card(3, i, 0, "4"));		 // 4
		deck->placeBack(new Card(2, i, 10, "3"));		 // 3
		deck->placeBack(new Card(1, i, 0, "2"));		 // 2
	}
	deck->shuffle();
	std::cout << "Taille du paquet : " << deck->getDeckSize() << std::endl;
}

void Briscola::play()
{
	int turnwinner, roundwinner;
	distributeCards(3);

	for (int i = 0; i < numberOfPlayers; i++)
	{
		if (players[i]->getPoints() == 2)
		{
			win = true;
			winner = i;
		}
	}
	if (!win)
	{
		//ROUND
		briscolaCard = deck->deal();
		std::cout << "L'atout est un " << briscolaCard->getSymbol() << " de " << briscolaCard->getCouleur() << " de rang " << briscolaCard->getRank() << " et de valeur " << briscolaCard->getValue() << std::endl
				  << std::endl;
		sleep(1);
		while (deck->getDeckSize() != 0)
		{
			//TURN
			for (indexOfCurrentPlayer = 0; indexOfCurrentPlayer < numberOfPlayers; indexOfCurrentPlayer++)
			{
				players[indexOfCurrentPlayer]->showHand();
				playCard();
			}
			for (int i = 0; i < numberOfPlayers; i++)
			{
				turnScores.push_back(playedCards[i]->getRank() + (playedCards[i]->getSuit() == briscolaCard->getSuit() ? 100 : 0));
			}
			turnwinner = evaluateScores(turnScores);

			std::cout << "turn winner is " << players[turnwinner]->getName() << " !" << std::endl;
			std::cout << " _ _ _ _ _ _ _ _ _ _" << std::endl;
			sleep(1);

			for (int i = 0; i < numberOfPlayers; i++)
			{
				roundScores[turnwinner] += playedCards[i]->getValue();
			}
			printScores(roundScores, "Round scores :");

			turnScores.clear();
			playedCards.clear();
			distributeCards(1);
		}
		printScores(roundScores, "Round scores :");
		roundwinner = evaluateScores(roundScores);
		players[roundwinner]->addPoints(1);

		std::cout << "Joueur " << players[roundwinner]->getName() << ", vous avez gagné 1 points avec un score de " << roundScores[roundwinner] << std::endl;

		roundScores.clear();
		setDeck();
	}
	std::cout << "Joueur " << players[winner]->getName() << ", vous avez gagné la partie ! " << std::endl;
}

void Briscola::playCard()
{
	int choice;

	std::cout << "Player : " << players[indexOfCurrentPlayer]->getName() << std::endl;
	while (true)
	{
		std::cout << "Choose a card of your hand. The index of this card must be between 1 and the number of cards you have." << std::endl;
		std::cin >> choice;
		std::cout << std::endl;
		if (choice > 0 && choice <= players[indexOfCurrentPlayer]->getNumberOfCards())
		{
			playedCard = players[indexOfCurrentPlayer]->remove(choice - 1);

			playedCards.push_back(playedCard);

			return;
		}
	}
}

int Briscola::evaluateScores(std::vector<int> scores)
{
	int max = 0;
	int player;
	printScores(scores,"Turn Score : ");
	for (int i = 0; i < numberOfPlayers; i++)
	{
		if (scores[i] > max)
		{
			max = scores[i];
			player = i;
		}
	}
	return player;
}

int Briscola::printScores(std::vector<int> scores, std::string message)
{
	std::cout << message << std::endl;
	for (int i = 0; i < numberOfPlayers; i++)
	{
		std::cout << players[i]->getName() << " : " << scores[i] << std::endl;
	}
	std::cout << std::endl;
}

std::ostream &operator<<(std::ostream &os, Briscola const &briscola)
{
	for (int i = 0; i < briscola.numberOfPlayers; i++)
	{
		os << "| " << briscola.players[i]->getName() << " , number of cards : " << briscola.players[i]->getNumberOfCards() << std::endl;
	}

	return os;
}