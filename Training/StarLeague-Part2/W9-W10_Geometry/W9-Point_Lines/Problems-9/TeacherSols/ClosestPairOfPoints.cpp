// Cloest Pair Of Points Divide and Conquer.cpp : 
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

bool compareY(const Point &p1, const Point &p2)
{
	if (p1.y == p2.y)
		return p1.x < p2.x;
	return p1.y < p2.y;
}

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
//sort v by y coordinates. Return the distance betweeen
//smallest pair of points in v.
unsigned long long processMidPoints(vector<Point> v)
{
	unsigned long long res = v[0].distance(v[1]);

	sort(v.begin(), v.end(), compareY);

	for (int i = 0; i < v.size(); i++)
		for (int j = i + 1; j < v.size() && (v[j].y - v[i].y) < res; j++)
			res = min(res, v[i].distance(v[j]));

	return res;
}
//------------------------------------------
//return closest distance amoung three points
unsigned long long threePoints(int startPos, int size)
{
	if (size <= 1)
		return BIGNUM;
	if (size == 2)
		return (pointVec[0].distance(pointVec[1]));

	Point p1 = pointVec[startPos];
	Point p2 = pointVec[startPos + 1];
	Point p3 = pointVec[startPos + 2];
	unsigned long long res = p1.distance(p2);
	res = min(res, p1.distance(p3));

	return min(res, p2.distance(p3));
}

//------------------------------------------
//classical divide and conquer algorithm to solve the
//closest pair of points problem.
unsigned long long go(int startPos, int endPos)
{
	int n = endPos - startPos + 1;
	if (n <= 3)
		return threePoints(startPos, n);

	int midPos = startPos + n / 2;

	Point midPoint = pointVec[midPos];

	unsigned long long dl = go(startPos, midPos);	//smallest distance on the left side
	unsigned long long dr = go(midPos, endPos);	//smallest distance on the right side

	unsigned long long d = min(dl, dr);
	vector <Point> midPointsVec;	//Points on the middle strip
	for (int i = startPos; i <= endPos; i++)
		if (pow(midPoint.x - pointVec[i].x,2) < d)
			midPointsVec.push_back(pointVec[i]);

	unsigned long long midDistance = d;
	if (midPointsVec.size() > 1)
		midDistance = processMidPoints(midPointsVec);
	return min(d, midDistance);
}
//------------------------------------------
int main()
{
	readInput();
	sort(pointVec.begin(), pointVec.end());
	unsigned long long res = go(0, pointVec.size() - 1);
	cout << res << endl;
	return 0;
}
