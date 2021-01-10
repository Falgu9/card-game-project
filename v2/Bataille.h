#ifndef __BATAILLE__H__
#define __BATAILLE__H__

#include "CardGame.h"

class Bataille : public CardGame
{
	friend std::ostream& operator<<(std::ostream& os, Bataille const& bataille);
public:
	Bataille();
	void play();
};

#endif

