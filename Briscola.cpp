#include <chrono>
#include "Briscola.h"

Briscola::Briscola() : playedCards(NULL), briscolaCard(NULL)
{

	if (numberOfPlayers != 2)
	{
		std::cout << "Error : Must be 2 players." << std::endl;
		exit(1);
	}

	setDeck();
	playedCards = new Linkedlist<Card *>();
}

Briscola::~Briscola()
{
	delete playedCards;
	delete briscolaCard;
}

void Briscola::setDeck()
{
	for (int i = 0; i < 4; i++)
	{
		deck->placeBack(new Card(12, i, 4, "Roi"));		 // King
		deck->placeBack(new Card(11, i, 3, "Reine"));	 // Queen
		deck->placeBack(new Card(10, i, 2, "Cavalier")); // Jack
		deck->placeBack(new Card(6, i, 0, "7"));		 // 7
		deck->placeBack(new Card(5, i, 0, "6"));		 // 6
		deck->placeBack(new Card(4, i, 0, "5"));		 // 5
		deck->placeBack(new Card(3, i, 0, "4"));		 // 4
		deck->placeBack(new Card(2, i, 10, "3"));		 // 3
		deck->placeBack(new Card(1, i, 0, "2"));		 // 2
		deck->placeBack(new Card(0, i, 11, "As"));		 // A
	}
	deck->shuffle();
	std::cout << "Taille du paquet : " << deck->getDeckSize() << std::endl;
}

void Briscola::setBricolaCard()
{
	briscolaCard = deck->deal();
}

void Briscola::play()
{

	distributeCards(3);
	setBricolaCard();
	std::cout << "L'atout est un " << briscolaCard->getSymbol() << " de " << briscolaCard->getCouleur() << " de rang " << briscolaCard->getRank() << " et de valeur " << briscolaCard->getValue() << std::endl;

	for (indexOfCurrentPlayer = 0; indexOfCurrentPlayer < numberOfPlayers; indexOfCurrentPlayer++)
	{
		players[indexOfCurrentPlayer]->showHand();
		playCard();
	}
}
void Briscola::playCard()
{
	int choice;

	std::cout << "Player : " << players[indexOfCurrentPlayer]->getName() << std::endl;
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

std::ostream &operator<<(std::ostream &os, Briscola const &briscola)
{
	for (int i = 0; i < briscola.numberOfPlayers; i++)
	{
		os << "| " << briscola.players[i]->getName() << " , number of cards : " << briscola.players[i]->getNumberOfCards() << std::endl;
	}

	return os;
}
