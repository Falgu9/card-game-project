#ifndef __CARD__H__
#define __CARD__H__

#include <string>

class Card
{
	friend std::ostream& operator<<(std::ostream& os, Card const& card);

private:
	static std::string ranks[14];
	static std::string suits[4];
	
	int rank;
	int suit;
	std::string symbol;
	int value;

public:
	Card();
	Card(int rank, int suit);
	Card(int rank, int suit, std::string symbol);
	Card(int rank, int suit, int value);

	int getRank() const;
	int getSuit() const;
	std::string getSymbol() const;
	int getValue() const;
	
	void setRank(int rank);
	void setSuit(int suit);
	void setSymbol(std::string symbol);
	void setValue(int value);
	
	bool operator<=(const Card& a) const;
	bool operator>=(const Card& a) const;
	bool operator<(const Card& a) const;
	bool operator>(const Card& a) const;
	bool operator==(const Card& a) const;
	bool operator!=(const Card& a) const;
};

#endif