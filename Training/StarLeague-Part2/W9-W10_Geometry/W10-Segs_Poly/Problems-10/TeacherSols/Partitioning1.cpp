// Partitioning the Farm Starleague.cpp : Offline quereis
// Osman Ay. July 2020.

#include <iostream>
#include <vector>
#include <algorithm>

#define MAX 1000000001

using namespace std;

struct Barn
{
	int x, y, c;
};

bool cmpX(Barn b1, Barn b2)
{
	if (b1.x == b2.x)
		return b1.y < b2.y;
	return b1.x < b2.x;
}

bool cmpY(Barn b1, Barn b2)
{
	if (b1.y == b2.y)
		return b1.x < b2.x;
	return b1.y < b2.y;
}

bool cmpC(Barn b1, Barn b2)
{
	return b1.c < b2.c;
}


struct Ans
{
	int a, b, c, d, id;
};

bool cmpId(Ans ans1, Ans ans2)
{
	return ans1.id < ans2.id;
}

//----------------------------------
int N, Q, total;
vector<Barn> X, Y, queries;
vector<Ans> answers;
//----------------------------------
void readInput()
{
	cin >> N >> Q;

	X.resize(N);
	for (int i = 0; i < N; i++)
	{
		cin >> X[i].x >> X[i].y >> X[i].c;
		total += X[i].c;
	}

	//dummy elements
	X.push_back({ 0, 0, 0 });
	X.push_back({ MAX, MAX, 0 });
	N += 2;

	queries.resize(Q);
	for (int i = 0; i < Q; i++)
	{
		cin >> queries[i].x >> queries[i].y;
		queries[i].c = i; //id of the query
	}
}
//----------------------------------
void go()
{
	Y = X;
	sort(X.begin(), X.end(), cmpX);


	vector<int> preSumX(N);
	preSumX[0] = X[0].c;
	for (int i = 1; i < N; i++)
		preSumX[i] = preSumX[i - 1] + X[i].c;


	sort(Y.begin(), Y.end(), cmpY);


	vector<int> preSumY(N);
	preSumY[0] = Y[0].c;
	for (int i = 1; i < N; i++)
		preSumY[i] = preSumY[i - 1] + Y[i].c;


	queries.push_back({ 0,0,0 }); //dummy query
	sort(queries.begin(), queries.end(), cmpX);

	int A = 0, B, C, D;
	int x = 0, y = 0;

	for (int i = 1; i <= Q; i++)
	{
		//Expand to the right (left-bottom rectangle)
		while (X[x].x < queries[i].x)
		{
			if (X[x].y < queries[i].y)
				A += X[x].c;
			x++;
		}

		//Expand or shrink on the top
		if (queries[i].y > queries[i - 1].y) //expanding to the up
		{
		    while (Y[y].y < queries[i-1].y)
		        y++;
		        
			while (Y[y].y < queries[i].y)
			{
				if (Y[y].x < queries[i - 1].x)
					A += Y[y].c;

				y++;
			}
		}
		else if (queries[i].y < queries[i - 1].y)
		{
		    while (Y[y].y > queries[i-1].y)
		        y--;
		        
			while (Y[y].y > queries[i].y)
			{
				if (Y[y].x < queries[i - 1].x)
					A -= Y[y].c;
				y--;
			}
		}

		auto it = lower_bound(X.begin(), X.end(), queries[i], cmpX);
		it--;
		int leftSum = preSumX[it - X.begin()];


		it = lower_bound(Y.begin(), Y.end(), queries[i], cmpY);	
		it--;
		int bottomSum = preSumY[it - Y.begin()];
		

		D = leftSum - A;
		B = bottomSum - A;
		C = total - (A + B + D);

		answers.push_back({ A,B,C,D, queries[i].c });
	}
}
//----------------------------------
void printResult()
{
	sort(answers.begin(), answers.end(), cmpId);
	for (auto ans : answers)
		cout << ans.a << " " << ans.b << " " << ans.c << " " << ans.d << endl;
}
//----------------------------------
int main()
{
	readInput();
	go();
	printResult();
}
