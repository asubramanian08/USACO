// Grazing Field.cpp : Coordinate Compression + flood fill
// Osman Ay. 2020 Feb.

//#include "pch.h"
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

//ifstream cin("grazing.in");
//ofstream cout("grazing.out");

struct Wall
{
	int x1, y1, x2, y2;

	bool isHorizontal()
	{
		return y1 == y2;
	}
};
//-------------------------------------------
int N, M, K;
vector<Wall> walls;
vector<int> X, Y;
vector<vector<int>> grid;
long long res; 
//-------------------------------------------
void readInput()
{
	cin >> N >> M >> K;

	for (int i = 0; i < K; i++)
	{
		Wall w;
		cin >> w.x1 >> w.y1 >> w.x2 >> w.y2;
	
		walls.push_back(w);

		X.push_back(w.x1);
		X.push_back(w.x2+1);
		Y.push_back(w.y1);
		Y.push_back(w.y2+1);
	} 
}
//-------------------------------------------
void compressGrid()
{
	//Add two artificial coordinates at the front and back.
	//Sort and remove duplicate coordinates
	X.push_back(1);
	sort(X.begin(), X.end());
	X.erase(unique(X.begin(), X.end()), X.end());
	X.push_back(N + 1);

	Y.push_back(1);
	sort(Y.begin(), Y.end());
	Y.erase(unique(Y.begin(), Y.end()), Y.end());
	Y.push_back(M + 1);

	//Create the compressed grid
	grid.resize(X.size(), vector<int>(Y.size(), 0));

	//Mark the walls on the compressed grid
	for (int i = 0; i < K; i++)
	{
		Wall w = walls[i];

		int y = lower_bound(Y.begin(), Y.end(), w.y1) - Y.begin();
		int x = lower_bound(X.begin(), X.end(), w.x1) - X.begin();

		if (w.isHorizontal())
		{
			while (X[x] <= w.x2)
			{
				grid[x][y] = 1;
				x++;
			}
		}
		else
		{
			while (Y[y] <= w.y2)
			{
				grid[x][y] = 1;
				y++;
			}
		}
	}
}
//-------------------------------------------
vector<int> xDir = { 0,1,0,-1 }, yDir = { 1,0,-1,0 };
void floodFill(int x, int y)
{
	if (x < 0 || X[x] >= N+1 || y < 0 || Y[y] >= M+1 || grid[x][y] != 0)
		return;

	grid[x][y] = 1;

	res += (X[x + 1] - X[x])*(Y[y + 1] - Y[y]);

	for (int i = 0; i < 4; i++)
		floodFill(x + xDir[i], y + yDir[i]);
}
//-------------------------------------------
int main()
{
    readInput(); 
	compressGrid();
	floodFill(0, 0);
	cout << res << endl;
}