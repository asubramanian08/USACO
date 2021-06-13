// Hay Bale Tower Starleague Gold.cpp : LIS. O(N*N)
// Osman Ay, December 2020

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

//ifstream cin("baletower.in");
//ofstream cout("baletower.out");

struct Bale
{
	bool friend operator < (const Bale &bale1, const Bale &bale2)
	{
		return bale1.w*bale1.d < bale2.w*bale2.d;
	}
	int w, d, h;

	Bale(int ww, int dd, int hh)
	{
		w = ww, d = dd, h = hh;
		if (w > d)
			swap(w, d);
	}
};

int N;
vector<Bale> bales;
//--------------------------------------
void readInput()
{
	cin >> N;
	for (int i = 0; i < N; i++)
	{
		int w, d, h;
		cin >> w >> d >> h;

		bales.push_back({ w, d, h });
		bales.push_back({ w, h, d });
		bales.push_back({ h, d, w });
	}
}
//--------------------------------------
int go()
{
	sort(bales.begin(), bales.end());
	vector<int> dp(3 * N, 0);

	for (int i = 0; i < 3 * N; i++)
	{
		dp[i] = bales[i].h;
		for (int j = 0; j < i; j++)
			if (bales[j].w < bales[i].w && bales[j].d < bales[i].d)
			{
				dp[i] = max(dp[i], dp[j] + bales[i].h);
			}
	}

	return *max_element(dp.begin(), dp.end());
}

//--------------------------------------
int main()
{
    readInput();
	cout << go() << endl;
}

