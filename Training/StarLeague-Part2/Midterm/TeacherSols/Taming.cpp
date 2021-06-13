// Taming the Herd Usaco 2018 Gold.cpp : DP
// Osman Ay, Jan 2021.

#include <fstream>
#include <vector>
#include <algorithm>

#define SIZE 105
#define BIGNUM 1000
using namespace std;

ifstream cin("taming.in");
ofstream cout("taming.out");

int N;
int A[SIZE];	//input array. 1-based.
//dp[i][j] is the best score for the first i breakouts and last breakout in day j
int dp[SIZE][SIZE];	
int res[SIZE];
//-----------------------------------
void readInput()
{
	cin >> N;
	for (int i = 1; i <= N; i++)
		cin >> A[i];
}
//-----------------------------------
void go()
{
	//initialize dp matrix to infinitive;
	for (int i = 1; i <= N; i++)
		for (int j = 1; j <= N; j++)
				dp[i][j] = BIGNUM;
	
	//initialize results to infinitive
	for (int i = 1; i <= N; i++)
		res[i] = BIGNUM;

	//Set the base case
	if (A[1] == 0)
		dp[1][1] = 0;
	else
		dp[1][1] = 1;

	//calculate the cost of the first breakout. It is always in day 1.
	res[1] = dp[1][1];
	for (int i = 2; i <= N; i++)
		if (A[i] != i - 1)
			res[1]++;

	//calculate the cost for the remaining breakouts
	for (int i = 2; i <= N; i++)
	{
		for (int j = i; j <= N; j++)		//ith breakout is in day j
		{
			//best cost between previous breakout and day j
			int cost = BIGNUM; //result for the ith breakout
			int temp;
			for (int k = i - 1; k < j; k++)	//k is the day of the previous breakout.
			{
				temp = dp[i-1][k];
				for (int m = k + 1; m < j; m++)
				{
					if (A[m] != m - k)
						temp++;
				}
				cost = min(cost, temp);
			}
			
			//cost of the day j
			if (A[j] != 0)
				cost++;

			dp[i][j] = cost; //best cost if i breakout occurs in day j.

			//cost of the days after day j
			for (int k = j + 1; k <= N; k++)
			{
				if (A[k] != k - j)
					cost++;
			}

 			res[i] = min(res[i], cost);
		}	
	}	
}
//-----------------------------------
void printResult()
{
	for (int i = 1; i <= N; i++) //nr breakouts
		cout << res[i] << endl;
}
//-----------------------------------
int main()
{
	readInput();
	go();
	printResult();

}


