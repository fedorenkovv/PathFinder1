
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <vector>

using namespace std;

const int SIZE = 16;
int a[SIZE][SIZE];

vector< pair<int, int> > wave;
vector< pair<int, int> > oldWave;
int finishX, finishY;

void display()
{
	for (int j = 0; j < SIZE; j++)
	{
		for (int i = 0; i < SIZE; i++)
		{
			switch (a[i][j])
			{
			case 999:
				std::cout << '#';
				break;
			case -2:
				std::cout << 'O';
				break;
			case -3:
				std::cout << '.';
				break;
			case -4:
				std::cout << 'X';
				break;
			default:
				std::cout << ' ';
				break;
			}

		}
		std::cout << std::endl;
	}
}
void initField()
{
	srand(time(NULL));
	for (int i = 1; i < SIZE - 1; i++)
	for (int j = 1; j < SIZE - 1; j++)
	{
		a[i][j] = -1;
		if (rand() % 5 == 0)
			a[i][j] = 999;
	}
	for (int j = 0; j < SIZE; j++)
	{
		a[0][j] = 999;
		a[j][0] = 999;
		a[j][SIZE - 1] = 999;
		a[SIZE - 1][j] = 999;
	}

}

void createPoints(pair<int, int> *p, pair<int, int> *b)
{
	a[p->first][p->second] = -1;
	a[b->first][b->second] = -1;

	oldWave.push_back(*p);
}

void findPath(pair<int, int> *p, pair<int, int> *b)
{
	int numStep = 0;
	int dx[] = { 0, 1, 0, -1 };
	int dy[] = { -1, 0, 1, 0 };
	oldWave.push_back(*p);
	a[p->first][p->second] = numStep;

	while (oldWave.size() > 0)
	{
		++numStep;
		wave.clear();
		for (vector<pair<int, int>>::iterator i = oldWave.begin(); i < oldWave.end(); i++)
		{
			const int dir = 4;
			for (int j = 0; j < dir; j++)
			{
				int nx = i->first + dx[j];
				int ny = i->second + dy[j];
				if (a[nx][ny] == -1)
				{
					wave.push_back(pair<int, int>(nx,ny));
					a[nx][ny] = numStep;
					if (nx == b->first - 1 && ny == b->second - 1)
						goto fin;
				}
			}
		}
		oldWave = wave;
	} 
fin:
	int x = b->first;
	int y = b->second;
	wave.clear();
	wave.push_back(pair<int, int>(x, y));
	while (a[x][y] != 0)
	{
		for (int d = 0; d < 4; d++)
		{
			int nx = x + dx[d];
			int ny = y + dy[d];
			if (a[x][y] - 1 == a[nx][ny])
			{
				x = nx;
				y = ny;
				wave.push_back(pair<int, int>(x, y));
				break;				
			}
		}
	}
	for (int i = 0; i < wave.size(); i++)
		a[wave[i].first][wave[i].second] = -3;
	a[p->first][p->second] = -4;
	a[b->first][b->second] = -2;


	system("cls");
	display();
}
int main()
{
	srand(time(0));
	initField();
	pair<int, int> p(2, 2);
	pair<int, int> b(12, 7);
	createPoints(&p, &b);
	display();
	findPath(&p,&b);


	return 0;
}