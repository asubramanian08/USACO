// Regions.cpp : Number of lines between to points.
// Osman Ay. 2020 Feb.

#include <iostream>

using namespace std;

struct Point
{
	int x, y;
};

struct Line
{
	int A, B, C; //Ax + By + C = 0;
	Line(Point p1, Point p2)
	{
		A = p2.y - p1.y;
		B = p1.x - p2.x;
		C = p1.x*(p1.y - p2.y) + p1.y*(p2.x - p1.x);
	}

	int testPoint(Point p)
	{
		return A * p.x + B * p.y + C;
	}
};

int main()
{
    Point p1, p2;
	cin >> p1.x >> p1.y >> p2.x >> p2.y;

	int n;
	cin >> n;

	int res = 0;

	for (int i = 0; i < n; i++)
	{
		Point p3, p4;

		cin >> p3.x >> p3.y >> p4.x >> p4.y;

		Line line(p3, p4);

		int temp1 = line.testPoint(p1);
		int temp2 = line.testPoint(p2);

		if (temp1 < 0 && temp2 > 0)
			res++;
		else if (temp1 > 0 && temp2 < 0)
		    res++;
	}

	cout << res << endl;
}

