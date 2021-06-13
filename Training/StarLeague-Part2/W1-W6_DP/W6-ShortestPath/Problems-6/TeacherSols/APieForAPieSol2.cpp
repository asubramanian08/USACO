// Pie For A Pie Usaco Gold.cpp : Solution in reverse with BFS.
// Osman Ay, October 2020.

#include <fstream>
#include <vector>
#include <queue>
#include <set>

using namespace std;

ifstream cin("piepie.in");
ofstream cout("piepie.out");

int N, D, BIGNUM;
vector<pair<int, int>> pies;
set<pair<int, int>> setB, setE; //first is value, second is id
vector<int> dp;
//---------------------------------
void readInput()
{
	cin >> N >> D;
	pies.resize(2 * N + 1);
	for (int i=1; i<=2*N; i++)
		cin >> pies[i].first >> pies[i].second;
}
//---------------------------------
void go2(int start)
{
	dp[start] = 1;
	queue<int> q;
	q.push(start);
	while (!q.empty())
	{
		int cur = q.front();
		q.pop();
		if (cur <= N) //Elsie receives the pie
		{
			int minVal = pies[cur].first - D;
			int maxVal = pies[cur].first;
			auto it = setB.lower_bound({ minVal, 0 });

			while (it != setB.end() && it->first <= maxVal)
			{
				if (dp[it->second] > dp[cur] + 1)
				{
					dp[it->second] = dp[cur] + 1;
					q.push({ it->second });
				}
				it++;
			}

		}
		else // Bessie receives the pie
		{
			int minVal = pies[cur].second - D;
			int maxVal = pies[cur].second;
			auto it = setE.lower_bound({ minVal, 0 });

			while (it != setE.end() && it->first <= maxVal)
			{
				if (dp[it->second] > dp[cur] + 1)
				{
					dp[it->second] = dp[cur] + 1;
					q.push({ it->second });
				}
				it++;
			}
		}
	}
	
}
//---------------------------------
void go()
{
	for (int i = 1; i <= N; i++)
		setE.insert({ pies[i].second, i });
	for (int i = N + 1; i <= 2 * N; i++)
		setB.insert({ pies[i].first, i });
	BIGNUM = 2 * N;
	dp.resize(2*N + 1, BIGNUM);
	for (int i = 1; i <= N; i++)
		if (pies[i].second == 0)
			go2(i);
	for (int i = N + 1; i <= 2 * N; i++)
		if (pies[i].first == 0)
			go2(i);
}
//---------------------------------
void printResult()
{
	for (int i = 1; i <= N; i++)
		cout << (dp[i] == BIGNUM ? -1 : dp[i]) << endl;
}
//---------------------------------
int main()
{
	readInput();
	go();
	printResult();
}