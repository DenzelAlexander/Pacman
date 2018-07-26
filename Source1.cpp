#include "Board.h"
#include "HighScores.h"
#include<conio.h>
class Board;

int DIR = 0;
int main()
{
    HighScores *Scores = new HighScores;

	char plyrStat = 1;
	Board *board = new Board;
	char dir = 2;
	string name;


	unsigned long int intrvl = 0;


	// This while loop will cotrol the game play and it will keep on running
	// until the game is over
	while (plyrStat)
	{
		// This condition will control the move of ghost
		// without it the ghost will keep on moving in the map with very high speed
		// so it will control the speed of ghost

		if (intrvl++ % 50000000 != 0)
		{
			continue;
		}
		intrvl = 1;
		system("cls");
		board->drawBoard();
		// This condition will decide save the character input by the user in variable dir and
		// if no character input then it will keep on executing it
		if (_kbhit())dir = _getch();

		// This swich case will decide the direction in which the user want to move
		switch (dir)
		{
		case 72://Up Arrow Key
			dir = 1; break;
		case 75://Left Arrow Key
			dir = 2; break;
		case 77://Right Arrow Key
			dir = 3; break;
		case 80://Down Arrow Key
			dir = 4; break;
		}
		// The below statement will update the pokemon map
		plyrStat = board->Update(dir);
		// Below if condition will execute if plyrstat becomes 0, it means that the packman power becomes zero
		// so the game becomes over
		if (plyrStat == 0)
		{
			system("cls");
			board->drawBoard();
			// Below statement will display the message on console
			cout << "Game over\n";
			if (Scores->scoreCheck(board->score) == true)
            {
                cin >> name;
                Scores->insert(board->score,name);
			}
			Scores->print();
			system("pause");
			break;
		}
		// Below if condition will execute if plyrstat becomes -1, it means that the packman has eaten all the powers
		// so the game becomes over
		else if (plyrStat == -1)
		{
			// Below statement will display the message on console
			cout << "You won!!!\n";
			system("pause");
		}
	}
	delete board;
}
