// Building a Fence.cpp : 
// Osman Ay. 2020 Feb.

#include <iostream>
#include <algorithm>

using namespace std;

int main()
{
	int N, M;
	cin >> N;

	M = N / 2;
	if (N % 2 == 0)
		M--;

	long long res = 0;
	for(int i=1; i<=M; i++)
		for (int j = 1; j <= M; j++)
		{
			int K = N - (i + j);
			if (K <= M)
			 res += K-1;
			else
			 res += (K-1) - (K-1-M)*2;
		}
	cout << res << endl;
}


