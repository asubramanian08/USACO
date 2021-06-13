// Sum of Manhattan Distances.cpp :

#include <iostream>
#include <vector>
#include <algorithm>

#define MOD 1000000007

using namespace std;

int N;
vector<int> xVec, yVec;

//-------------------------------------
void readInput()
{
	cin >> N;
	xVec.resize(N);
	yVec.resize(N);
	for (int i = 0; i < N; i++)
	{
		cin >> xVec[i] >> yVec[i];
	}
}
//-------------------------------------
long long go(vector<int> &v)
{
	sort(v.begin(), v.end());
	long long res = 0;
	long long sum = 0;
	for (int i = 1; i < N; i++)
	{
		sum += i*(v[i] - v[i - 1]);
		sum = sum % MOD;
		res += sum;
		res = res % MOD;
	}

	return res;
}
//-------------------------------------
int main()
{
    readInput();
	cout << (go(xVec) + go(yVec)) % MOD << endl;
}


