#ifndef BOARD_H
#define BOARD_H
#include <iostream>
#include <cwchar>
#include <stdlib.h>
#include <time.h>
#include <set>
#include <windows.h>
#include <conio.h>
using namespace std;
struct Loc
{
	int x;
	int y;
	char v;
	int s;
	char d;
	bool operator<(const Loc &rhs) const { return s < rhs.s; }
	bool operator==(const Loc &rhs) const{ return x == rhs.x && y == rhs.y; }
};

class Board
{
private:
	// This will store the map in board array
	char board[18][45] =
	{ // 25 45
		"==========PACMAN-ETA===========",
		"|ooooooooooooooooooooooooooooo|",
		"|_____|oooo|_____|o|________ o|",
		"|_____|oooo|_____|o|________|o|",
		"|ooooooo|ooooooXo|o|oooooooooo|",
		"|_____|o|________|o|oooooooooo|",
		"|_____|ooooooooooooooooooooooo|",
		"|_______|oo|__________|ooooooo|",
		"|oooooooooooooo|______|ooooooo|",
		"|_______|oo|ooooo|____|ooooooo|",
		"|_______|oo|oooooooooooooooooo|",
		"|oooooooooo|___________|oooooo|",
		"|oo|___________________|oooooo|",
		"|oo|__________|ooooooooooooooo|",
		"|ooooooooooooooo|___________|o|",
		"|o|_________________________|o|",
		"|oooooooooooooooooo@oooooooooo|",
		"==========PACMAN-ETA==========="
	};

	Loc pLoc;
	Loc gLoc;
	char dir;
	set<Loc> path;

public:
	// This is a constructor to initialize the member variables
	Board() :dir(2){
		srand((unsigned)time((time_t*)NULL));
		gLoc.x = 16;
		gLoc.y = 19;
		gLoc.v = 'o';
		gLoc.s = 2;
		gLoc.d = 3;
		pLoc.x = 4;
		pLoc.y = 15;
		pLoc.s = 1;
	}
	// This is a destructor
	virtual ~Board();
	// Below function will display the complete board on console
	void drawBoard()
	{
		for (int i = 0; i < 18; i++) {
			printf("%s\n", board[i]);
		}
		cout << endl << "Score: "<< score << endl;
	}
    int score = 0;
	// This function will update the map according to the direction passed as paraameter
	char Update(char dir, Loc *lol = nullptr)
	{
		static int done = 0;
		int total = 253;
		static set<Loc>::iterator it;
		char dr = dir;
		Loc *l;
		char dd;
		// This will execute if the piointer is initially null
		if (lol == nullptr)
		{
			l = &pLoc; dd = this->dir;
		}
		// if the pointer lol is not null then the else will execute
		else
		{
			l = lol; dd = lol->d;
		}
		Loc loc = pLoc;

		// This switch will execute according to the direction passed as parameter and will have 4 blocks for each direction
		switch ((int)dir)
		{
			// This case will execute if the direction is 1, which means if the direction is left
		case 1:
			if (lol)
			{
				// If the charater at left is _ or | then following if will execute
				if (board[l->x - 1][l->y] == '_' || l->x == 1 || board[l->x - 1][l->y] == '|')
				{
					if (board[l->x][l->y - 1] == 'o')
                    {
                        return Update(2, l);
                    }
                    if(board[l->x][l->y - 1] == ' ')
                    {
						return Update(2, l);
                    }
					if (board[l->x][l->y + 1] == 'o')
                    {
                        return Update(3, l);
					}
                    if(board[l->x][l->y + 1] == ' ')
                    {
						return Update(3, l);
                    }
					if (board[l->x + 1][l->y] == 'o')
					{
                        return Update(4, l);
                    }
                    if(board[l->x + 1][l->y] == ' ')
                    {
						return Update(4, l);
                    }
				}
			}
			if (dir == this->dir && (board[l->x - 1][l->y] == '_' || l->x - 1 == 0 || board[l->x - 1][l->y] == '|'))
			{
				break;
			}
			if (board[l->x - 1][l->y] == '_' || l->x - 1 == 0 || board[l->x - 1][l->y] == '|')
			{
				return Update(this->dir, lol);
			}
			l->x -= 1;
			dr = 1;
			break;
		case 2:
			// This case will execute if the direction is 2, which means if the direction is up
			if (lol)
			{
				// If the charater at up is _ or | then following if will execute
				if (board[l->x][l->y - 1] == '|' || board[l->x][l->y - 1] == '_')
				{
					if (board[l->x - 1][l->y] == 'o')
                    {
                        return Update(1, l);
					}
                    if(board[l->x - 1][l->y] == ' ')
                    {
						return Update(1, l);
                    }
					if (board[l->x + 1][l->y] == 'o')
                    {
                        return Update(4, l);
					}
                    if(board[l->x + 1][l->y] == ' ')
                    {
						return Update(4, l);
                    }
					if (board[l->x][l->y + 1] == 'o')
                    {
                        return Update(3, l);
					}
					if (board[l->x][l->y + 1] == ' ')
                    {
						return Update(3, l);
					}
				}
			}
			if ((dir == dd && board[l->x][l->y - 1] == '|') || (board[l->x][l->y - 1] == '_'))
			{
				break;
			}
			if (board[l->x][l->y - 1] == '|' || board[l->x][l->y - 1] == '_')
				return Update(dd, lol);
			l->y -= 1;
			dr = 2;
			break;
		case 3:
			// This case will execute if the direction is 3, which means if the direction is down
			if (lol)
			{
				// If the charater at down is _ or | then following if will execute
				if (board[l->x][l->y + 1] == '|' || board[l->x][l->y - 1] == '_')
				{
					if (board[l->x - 1][l->y] == 'o')
                    {
                    return Update(1, l);
					}
                    if(board[l->x - 1][l->y] == ' ')
                    {
						return Update(1, l);
                    }
					if (board[l->x + 1][l->y] == 'o')
                    {
                        return Update(4, l);
					}
                    if (board[l->x + 1][l->y] == ' ')
                    {
						return Update(4, l);
                    }
					if (board[l->x][l->y - 1] == 'o')
                    {
                            return Update(2, l);
                    }
                    if(board[l->x][l->y - 1] == ' ')
                    {
						return Update(2, l);
                    }
				}
			}
			if ((dir == dd && board[l->x][l->y + 1] == '|') || (board[l->x][l->y - 1] == '_'))
				break;
			if (board[l->x][l->y + 1] == '|' || board[l->x][l->y - 1] == '_')
				return Update(dd, lol);
			l->y += 1;
			dr = 3;
			break;
		case 4:
			// This case will execute if the direction is 4, which means if the direction is right
			if (lol)
			{
				// If the charater at right is _ or | then following if will execute
				if (board[l->x + 1][l->y] == '_' || l->x == 16 || board[l->x + 1][l->y] == '|')
				{
					if (board[l->x][l->y - 1] == 'o')
                    {
						return Update(2, l);
					}
                    if (board[l->x][l->y - 1] == ' ')
                    {
                        return Update(2, l);
                    }
					if (board[l->x][l->y + 1] == 'o')
                    {
						return Update(3, l);
					}
                    if(board[l->x][l->y + 1] == ' ')
                    {
                        return Update(3, l);
                    }
					if (board[l->x - 1][l->y] == 'o')
                    {
						return Update(1, l);
					}
                    if(board[l->x - 1][l->y] == ' ')
                    {
                        return Update(1, l);
                    }
				}
			}
			if (dir == dd && (board[l->x + 1][l->y] == '_' || l->x + 1 == 17 || board[l->x + 1][l->y] == '|'))
				break;
			if (board[l->x + 1][l->y] == '_' || l->x + 1 == 17 || board[l->x + 1][l->y] == '|')
				return Update(dd, lol);
			l->x += 1;
			dr = 4;
			break;
		default:
			break;
		}

		if (lol)return dr;

		if (board[l->x][l->y] == 'o')
        {
            score++;
			done++;
		}
		if (done == total)
			return -1;
		board[loc.x][loc.y] = ' ';
		board[l->x][l->y] = 'X';
		if (!(pLoc == loc))
		{

			pLoc.s++;
			pLoc.d = dr;
			path.insert(pLoc);
			it = path.begin();
			if (path.size() >= 20)
			{
				path.erase(*it);
			}
		}


		this->dir = dr;


		static bool found = false;
		static int x = 3, y = 0;

		static char gd = 3;
		set<Loc>::iterator c = path.begin();
		for (c; c != path.end(); c++)
		{
			if ((*c) == gLoc)
				break;
		}
		if (c != path.end())
		{

			found = true;
			gd = c->d;
			path.erase(path.begin(), c);
		}


		if (gLoc.x == pLoc.x && gLoc.y == pLoc.y)
		{
			board[gLoc.x][gLoc.y] = '@';
			return 0;
		}

		board[gLoc.x][gLoc.y] = gLoc.v;
		if (!found)
		{
			y = rand() % 6;
			if (x == y)
			{
				x = 0;
				gd = (rand() % 4) + 1;
			}
			gd = Update(gd, &gLoc);
			gLoc.d = gd;
		}
		else if (path.size()>0)
		{
			it = path.begin();
			Update(it->d, &gLoc);
			path.erase(*it);
		}

		gLoc.v = board[gLoc.x][gLoc.y];
		board[gLoc.x][gLoc.y] = '@';


		if (gLoc.x == pLoc.x && gLoc.y == pLoc.y)
		{
			board[gLoc.x][gLoc.y] = '@';
			return 0;
		}
		return this->dir;
	}
};
Board::~Board(){};

#endif // BOARD_H
