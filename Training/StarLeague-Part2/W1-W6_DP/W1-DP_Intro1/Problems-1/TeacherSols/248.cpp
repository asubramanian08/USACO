// 248 Usaco 2016 US Open Gold.cpp : DP O(N*N*N). Chain Matrix Multiplication
// Osman Ay. Septembper 2016.

#include <fstream>
#include <vector>
#include <algorithm>

using namespace std;

ifstream cin("248.in");
ofstream cout("248.out");

int N,result;
vector<int> numbers;
//-----------------------------------------------
void readInput()
{
	cin >> N;
	numbers.resize(N);
	for (int i = 0; i < N; i++)
	{
		cin >> numbers[i];
		result = max(result, numbers[i]);
	}
	cin.close();
}
//-----------------------------------------------
void go()
{
	vector<vector<int>> dp; //dp[i][j] is the best score starting in i with the length j
	dp.resize(N, vector<int>(N+1, 0));

	for (int i = 0; i < N; i++)
	{
		//dp[i][0] = 0;
		dp[i][1] = numbers[i];
	}

	for (int len = 2; len <= N; len++)
	{
		for (int i = 0; i <= N-len; i++)
		{
			int temp = 0;
			for (int k = 1; k < len; k++)
			{
				int val1 = dp[i][k];
				int val2 = dp[i + k][len - k];
				if (val1 == val2)
					temp = max(temp, val1 + 1);
				result = max(result, temp);
			}
			if (temp > 0)
				dp[i][len] = temp;
		}
	}
}
//-----------------------------------------------
int main()
{
    readInput(); 
	go();
	cout << result << endl;
	cout.close();
	return 0;
}