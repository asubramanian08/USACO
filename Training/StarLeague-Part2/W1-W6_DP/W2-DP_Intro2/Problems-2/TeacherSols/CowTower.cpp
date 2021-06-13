// Cow Tower Starleague Gold.cpp : DP. O(N*N) time, O(N) space.
// Osman Ay, December 2020.

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

//ifstream cin("tower.in");
//ofstream cout("tower.out");

int N;
vector<pair<int, int> > cows;

//---------------------------------
void readInput()
{
	cin >> N;
	for (int i = 0; i < N; i++)
	{
		int s, w;
		cin >> w >> s;

		cows.push_back(make_pair(s, w));
	}
	N = cows.size();
}
//---------------------------------
int go()
{
	sort(cows.begin(), cows.end());
	vector<int> dp(N + 1, INT_MAX / 2);
	dp[0] = 0;

	int res = 0;

	for (int i = 0; i < N; i++)
	{
		for (int j = res; j >= 0; j--)
		{
			if (cows[i].first >= dp[j] + cows[i].second && dp[j + 1] > dp[j] + cows[i].second)
			{
				dp[j + 1] = dp[j] + cows[i].second;
				res = max(res, j + 1);
			}
		}
	}

	return res;
}
//---------------------------------
int main()
{
	readInput();
	cout << go() << endl;
}