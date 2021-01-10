#include <iostream>
#include "Bataille.h"
#include "HuitAmericain.h"
#include "Briscola.h"
#include "Uno.h"
#include "Belote.h"

using namespace std;

int main()
{
	Bataille *j1;
	HuitAmericain *j2;
	Briscola *j3;
	Uno *j4;
	Belote *j5;

	int game = -1;

	while (game != 3)
	{
		cout << "Wich game do you want to play ?" << endl << "Bataille : 1, HuitAmericain : 2, Briscola : 3, Uno : 4, Belote : 5, leave the game : other key" << endl;
		cin >> game;
		switch (game)
		{
		case 1:
			j1 = new Bataille();
			j1 -> play();
			delete j1;
			break;
		case 2:
			j2 = new HuitAmericain();
			j2 -> play();
			delete j2;
			break;
		case 3:
			j3 = new Briscola();
			j3 -> play();
			delete j3;
			break;
		case 4:
			j4 = new Uno();
			j4 -> play();
			delete j4;
			break;
		case 5:
			j5 = new Belote();
			j5 -> play();
			delete j5;
			break;
		default:
			game = 3;
			break;
		}
	}

  	return 0;
}
