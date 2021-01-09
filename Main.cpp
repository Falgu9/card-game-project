#include <iostream>
#include "Belote.h"
#include "Briscola.h"
using namespace std;

int main()
{
	int game;
	std::cout << "Wich game do you want to play ?" << std::endl <<  "Briscola : 1, Belote : 2" << std::endl;
	std::cin >> game;
	Briscola *a;
	Belote *b;
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
		break;
	}
	return 1;
}
