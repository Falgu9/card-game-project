#include <chrono>
#include "Briscola.h"

Briscola::Briscola() : win(false), winner(numberOfPlayers)
{
	int maxPlayers = 5,minPlayers = 1;
	setPlayers(minPlayers,maxPlayers);

	playedCards = std::vector<Card *>();
	briscolaCard = new Card();
	turnScores = std::vector<int>(), roundScores = std::vector<int>(numberOfPlayers);
}

Briscola::~Briscola()
{
	/*delete &playedCards;
	delete briscolaCard;
	delete &turnScores;
	delete &roundScores;*/
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
	/*players[0]->addPoints(2);
	winCheck();*/
	
	//DEBUT DU JEU
	int turnwinner, roundwinner;
	std::cout << "Bienvenue dans le Briscola !" << std::endl;
	sleep(1);
	while (!win)
	{
		//DEBUT DU ROUND
		setDeck();
		distributeCards(3);

		briscolaCard = deck->deal();
		std::cout << "L'atout est " << briscolaCard->getSymbol() << " de " << briscolaCard->getCouleur() << " de rang " << briscolaCard->getRank() << " et de valeur " << briscolaCard->getValue() << std::endl
				  << std::endl;
		sleep(1);
		while (players[0]->getNumberOfCards() != 0)
		{
			//DEBUT DU TOUR
			std::cout << "Taille du paquet : " << deck->getDeckSize() << std::endl << std::endl;
			for (indexOfCurrentPlayer = 0; indexOfCurrentPlayer < numberOfPlayers; indexOfCurrentPlayer++)
			{
				players[indexOfCurrentPlayer]->showHand();
				playCard();
			}
			for (int i = 0; i < numberOfPlayers; i++)
			{
				turnScores.push_back(playedCards[i]->getRank() + (playedCards[i]->getSuit() == briscolaCard->getSuit() ? 100 : 0));
			}
			//printScores(turnScores, "Turn scores : ");
			turnwinner = evaluateScores(turnScores);
			if (turnwinner != numberOfPlayers)
			{
				std::cout << "Joueur " << players[turnwinner]->getName() << ", vous gagnez ce tour !" << std::endl;
				for (int i = 0; i < numberOfPlayers; i++)
				{
					roundScores[turnwinner] += playedCards[i]->getValue();
				}
			}
			else if (turnwinner == numberOfPlayers)
			{
				std::cout << "Egalité !" << std::endl;
			}
			std::cout << "_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _" << std::endl
					  << std::endl;
			sleep(1);
			printScores(roundScores, "Round scores :");

			if (deck->getDeckSize() == numberOfPlayers-1)
			{
				deck->placeBack(briscolaCard);
				distributeCards(1);
				std::cout << "La carte Briscola a ete rajoutée dans le deck." << std::endl;
				std::cout << "Vous piochez une carte." << std::endl;
				sleep(1);
			}
			else if (deck->getDeckSize() != 0)
			{
				distributeCards(1);
				std::cout << "Vous piochez une carte." << std::endl;
				sleep(1);
			}
			turnScores.clear();
			playedCards.clear();
			// FIN DU TOUR
		}
		roundwinner = evaluateScores(roundScores);
		if (roundwinner != numberOfPlayers)
		{
			players[roundwinner]->addPoints(1);

			std::cout << "Joueur " << players[roundwinner]->getName() << ", vous avez gagné 1 points avec un score de " << roundScores[roundwinner] << std::endl;
		}
		else if (roundwinner == numberOfPlayers)
		{
			std::cout << "Egalité !" << std::endl;
		}
		for (int i = 0; i < numberOfPlayers; i++)
		{
			std::cout << players[i]->getName() << " : " << players[i]->getPoints() << " pts" << std::endl;
		}
		std::cout << "_ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _ _" << std::endl
				  << std::endl;
		winCheck();
		std::fill(roundScores.begin(), roundScores.end(), 0);
		//FIN DU ROUND
	}
	std::cout << "Joueur " << players[winner]->getName() << ", vous avez gagné la partie ! " << std::endl;
	//FIN DU JEU
}

void Briscola::playCard()
{
	int choice;
	bool loop = true;
	while (loop)
	{
		std::cout << "Joueur " << players[indexOfCurrentPlayer]->getName() << ", choisissez une carte de votre main. L'index de cette carte doit etre situé entre 1 et " << players[indexOfCurrentPlayer]->getNumberOfCards() << "." << std::endl;
		std::cout << "Atout " << briscolaCard->getCouleur() << "." << std::endl;
		std::cin >> choice;
		std::cout << std::endl;
		if (choice > 0 && choice <= players[indexOfCurrentPlayer]->getNumberOfCards())
		{
			playedCard = players[indexOfCurrentPlayer]->remove(choice - 1);
			playedCards.push_back(playedCard);
			loop = false;
		}
	}
}

void Briscola::winCheck()
{
	for (int i = 0; i < numberOfPlayers; i++)
	{
		if (players[i]->getPoints() == 2)
		{
			win = true;
			winner = i;
		}
	}
}

int Briscola::evaluateScores(std::vector<int> scores)
{
	int max = 0;
	int player;
	int eq = 0;
	for (int i = 0; i < numberOfPlayers; i++)
	{
		if (scores[i] > max)
		{
			max = scores[i];
			player = i;
		}
	}
	for (int i = 0; i < numberOfPlayers; i++)
	{
		if (scores[i] == max)
		{
			eq++;
		}
	}
	if (eq > 1)
	{
		player = numberOfPlayers;
	}
	return player;
}

void Briscola::printScores(std::vector<int> scores, std::string message)
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