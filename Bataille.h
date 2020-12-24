#ifndef __BATAILLE__H__
#define __BATAILLE__H__

#include "Game.h"

class Bataille : public Game
{
	friend std::ostream& operator<<(std::ostream& os, Bataille const& bataille);
public:
	void play();
};

#endif

