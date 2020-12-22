#ifndef __CARD__H__
#define __CARD__H__

#include <string>

class Card
{
	friend std::ostream& operator<<(std::ostream& os, const Card& card);

private:
	static std::string rankAsStr[13];
	static std::string suitAsStr[4];
	
	int rank;
	int suit;

public:
	Card();
	Card(int rank, int suit);

	void setRank(int rank);
	void setSuit(int suit);

	int getRank() const;
	int getSuit() const;
};

#endif