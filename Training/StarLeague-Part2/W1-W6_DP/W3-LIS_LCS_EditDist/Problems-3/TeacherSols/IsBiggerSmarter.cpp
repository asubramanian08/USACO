// Is Bigger Smarter.cpp : LIS solution. O(NlogN)

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int N;
vector<pair<int, int>> pairs; //size and IQ
//--------------------------------------
void readInput()
{
	cin >> N;
	pairs.resize(N);
	for (int i = 0; i < N; i++)
		cin >> pairs[i].first >> pairs[i].second;
}
//--------------------------------------
int go()
{
	sort(pairs.begin(), pairs.end());

	vector<int> tail;

	for (int i = N-1; i >=0; i--)
	{
		int cur = pairs[i].second;

		if (tail.empty() || cur > tail.back())
			tail.push_back(cur);
		else
		{
			auto it = lower_bound(tail.begin(), tail.end(), cur);
			*it = cur;
		}
	}
	
	return tail.size();
}
//--------------------------------------
int main()
{
	readInput();
	cout << go() << endl;
}



