#include <iostream>
#include "Belote.h"
#include "Briscola.h"
using namespace std;

int main()
{
	Briscola *a;
	Belote *b;
	int game;

	while (game != 3)
	{
		std::cout << "Wich game do you want to play ?" << std::endl
				  << "Briscola : 1, Belote : 2, Leave the game : other key" << std::endl;
		std::cin >> game;
		switch (game)
		{
		case 1:
			a = new Briscola();
			a->play();
			break;
		case 2:
			b = new Belote();
			b->play();
			break;
		default:
			game = 3;
			break;
		}
	}

	return 1;
}
