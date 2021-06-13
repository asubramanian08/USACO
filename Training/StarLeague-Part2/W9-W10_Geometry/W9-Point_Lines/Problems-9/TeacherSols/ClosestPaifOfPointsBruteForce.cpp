// Cloest Pair Of Points Brute Force.cpp : 
// Osman Ay. Feb 2020.

#include <iostream>
#include <vector>
#include <algorithm>
#include <limits>

#define BIGNUM 8000000000000

using namespace std;

struct Point
{
	bool friend operator < (const Point &p1, const Point &p2)
	{
		if (p1.x == p2.x)
			return p1.y < p2.y;
		return p1.x < p2.x;
	}

	unsigned long long distance(const Point &p2)
	{
		return pow(x - p2.x, 2) + pow(y - p2.y, 2);
	}

	int x, y;
};

int N;
vector <Point> pointVec;
//------------------------------------------
void readInput()
{
	cin >> N;
	pointVec.resize(N);
	for (int i = 0; i < N; i++)
		cin >> pointVec[i].x >> pointVec[i].y;
}
//------------------------------------------
unsigned long long go()
{
	unsigned long long res = BIGNUM;

	for (int i = 0; i < pointVec.size(); i++)
		for (int j = i + 1; j < pointVec.size() && pow(pointVec[j].x - pointVec[i].x ,2) < res; j++)
			res = min(res, pointVec[i].distance(pointVec[j]));

	return res;
}
//------------------------------------------
int main()
{
	readInput();
	sort(pointVec.begin(), pointVec.end());
	cout << go() << endl;
	return 0;
}

