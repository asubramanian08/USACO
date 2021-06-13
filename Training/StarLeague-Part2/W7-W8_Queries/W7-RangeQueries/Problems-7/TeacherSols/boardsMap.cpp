// Springboards Usaco Gold.cpp: Keeping the best springs in a map
// Osman Ay, November 2020.

#include <fstream>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

ifstream cin("boards.in");
ofstream cout("boards.out");

struct Point
{
	int id, x, y, type; //type 0 is in, type 1 is out.
	int x2, y2;			//other end point of the springboard.
};

bool cmpX(const Point &p1, const Point &p2)
{
	if (p1.x == p2.x)
		return p1.y < p2.y;
	return p1.x < p2.x;
}

int N, M, K;
vector<Point> points, inVec;
vector<int> inVal;
//---------------------------------------------
void readInput()
{
	cin >> N >> M;

	for (int i = 0; i < M; i++)
	{
		int x1, y1, x2, y2;
		cin >> x1 >> y1 >> x2 >> y2;

		points.push_back({ i, x1, y1, 0, x2, y2 });
		points.push_back({ i, x2, y2, 1, x1, y1 });		
	}

	points.push_back({M, N, N, 0, N, N});
	points.push_back({ M, N, N, 1, N, N });
}
//---------------------------------------------
int go()
{
	map<int, int> m; //y coodinate and min value

	m[0] = 0;
	m[N + 1] = -2*N;

	sort(points.begin(), points.end(), cmpX);

	inVal.resize(M + 1, 0);

	for (auto p1:points)
	{
		if (p1.type == 1)
		{
			int val = inVal[p1.id] + p1.x2 - p1.x + p1.y2 - p1.y;

			if (m[p1.y] <= val)
				continue;

			m[p1.y] = val;

			auto it = m.lower_bound(p1.y + 1);
			while (it->second > val)
			{
				it->second = val;
				it++;
			}
			continue;
		}

		auto it = m.lower_bound(p1.y + 1);
		it--;
		inVal[p1.id] = it->second;
	}

	return 2*N + m[N];
}
//---------------------------------------------
int main()
{
    readInput(); 
	cout << go() << endl;
}

