// Sleepwalking Cows.cpp : Fenwick Tree solution
// Osman Ay. March 2020.

#include <fstream>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

ifstream cin("swalking2.in");
ofstream cout("swalking2.out");

struct BIT
{
	map <int, int> tree;
	int n;
	//--------------------------------------------
	//Create an empty tree
	void init(int size)
	{
		n = size;
	}
	//--------------------------------------------
	//Point update.
	void update(int i, int delta)
	{
		while (i < n)
		{
			tree[i] += delta;
			i += i & (-i); //add lowest set bit
		}
	}
	//--------------------------------------------
	int prefixSum(int i)
	{
		int sum = 0;
		while (i > 0)
		{
			sum += tree[i];
			i -= i & (-i); //subtract lowest set bit.
		}
		return sum;
	}
	//--------------------------------------------
	int rangeSum(int i, int j)
	{
		return prefixSum(j) - prefixSum(i - 1);
	}
};

int N, M, K, X;
vector<int> cows;
BIT bit;

//--------------------------------------------
void readInput()
{
	cin >> N >> M >> K >> X;
	bit.init(M + 1);

	cows.resize(N + 1);
	for (int i = 1; i <= N; i++)
	{
		int a;
		cin >> a;
		cows[i] = a;
		bit.update(a, 1);
	}
}
//--------------------------------------------
void go()
{
	for (int i = 0; i < K; i++)
	{
		int a, b, c;
		cin >> a >> b >> c;
		if (a == 0) //update
		{
			bit.update(cows[b], -1);
			cows[b] = c;
			bit.update(c, 1);
		}
		else //range query
		{
			int temp = bit.rangeSum(b, c);
			if (temp > X)
				cout << temp << endl;
		}
	}
}
//--------------------------------------------
int main()
{
	readInput();
	go();
}


