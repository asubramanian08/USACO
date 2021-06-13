// Springboards Usaco Gold Sol 2.cpp : 
// Osman Ay, November 2020.

#include <fstream>
#include <vector>
#include <algorithm>
#include <set>

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
vector<Point> points, inVec, outVec;
vector<int> Y, sqrtVec, blocks, inVal;
int blockSize, nrBlocks;

//---------------------------------------------
//SQRT Decomposition
void init()
{
	sqrtVec.resize(K, 0);
	blocks.resize(nrBlocks, 0);
}

void update(int i, int val)
{
	if (sqrtVec[i] <= val)
		return;

	blocks[i / blockSize] = min(blocks[i / blockSize], val);
	sqrtVec[i] = val;
}

int minQuery(int pos)
{
	int res = N + N;
	for (int i = 0; i < pos / blockSize; i++)
		res = min(res, blocks[i]);

	while (pos%blockSize > 0)
	{
		res = min(res, sqrtVec[pos]);
		pos--;
	}
	return min(res, sqrtVec[pos]);
}
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

		Y.push_back(y2);
		
	}

	points.push_back({M, N, N, 0, N, N});
	points.push_back({ M, N, N, 1, N, N });
	Y.push_back(N);
}
//---------------------------------------------
void go()
{
	sort(Y.begin(), Y.end());
	Y.resize(unique(Y.begin(), Y.end()) - Y.begin());
	K = Y.size();

	blockSize = (int)sqrt(K);
	nrBlocks = K / blockSize + K % blockSize;

	init();

	sort(points.begin(), points.end(), cmpX);

	inVal.resize(M + 1, 0);

	for (auto p1:points)
	{
		if (p1.type == 1)
		{
			int y = lower_bound(Y.begin(), Y.end(), p1.y) - Y.begin();
			int val = inVal[p1.id] + p1.x2 - p1.x + p1.y2 - p1.y;
			update(y, val);
			continue;
		}

		int y = lower_bound(Y.begin(), Y.end(), p1.y) - Y.begin();
		inVal[p1.id] = minQuery(y);
	}
}
//---------------------------------------------
int main()
{
    readInput(); 
	go();
	cout << N + N + sqrtVec[K - 1] << endl;
}

