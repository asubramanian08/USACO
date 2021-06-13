// Milk Collect : DP buttom-up design. Coint Change algorithm
// Osman Ay. December 2020.

#include <iostream>
#include <vector>
#include <algorithm>

#define MOD 1000000007

using namespace std;

//ifstream cin("milkcollect.in");
//ofstream cout("milkcollect.out");

int N, L;
vector<int> numbers;
//----------------------------------------
void readInput()
{
	cin >> N >> L;
    numbers.resize(N);
	for (int i = 0; i < N; i++)
	    cin >> numbers[i];	
}
//----------------------------------------
long long go()
{
	vector<long long> dp(L + 1, 0);
	dp[0] = 1; //base case

	for (int i = 1; i <= L; i++)
		for (int j = 0; j < N; j++)
			if (numbers[j] <= i)
				dp[i] = (dp[i] + dp[i - numbers[j]]) % MOD;

	return dp[L];
}
//----------------------------------------
int main()
{
	readInput();
    cout<< go() <<endl; 
}





