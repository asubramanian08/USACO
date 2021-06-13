// Fence Painting Starleague Gold.cpp : DP. O(N*N) time and O(N) space.
// Osman Ay, December 2020.

#include <iostream>
#include <vector>
#include <algorithm>

#define BIGNUM 1000000000

using namespace std;

//ifstream cin("fencepaint.in");
//ofstream cout("fencepaint.out");

int main()
{
    int L, N;
	cin >> L >> N;
	vector<int> dp(L + 1, BIGNUM);

	for (int i = 0; i < N; i++)
	{
		int d, k;
		cin >> d >> k;
		dp[d] = min(dp[d], k);
	}

	for (int i = 1; i <= L; i++)
		for (int j = 1; j <= i / 2; j++)
			dp[i] = min(dp[i], dp[j] + dp[i - j]);

	cout << (dp[L] < BIGNUM ? dp[L] : -1) << endl;
}

