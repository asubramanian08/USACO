//Total distance between points in manhatten distance

#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;
#define MOD 1000000007

int cmp(const void *p1, const void *p2)
{
    return *((int *)p1) - *((int *)p2);
}

int main(void)
{
    //read
    /*FILE *junk;
    junk = freopen("sumdist.in", "r", stdin);
    junk = freopen("sumdist.out", "w", stdout);*/
    int points;
    cin >> points;
    int *xPts = new int[points];
    int *yPts = new int[points];
    for (int i = 0; i < points; i++)
        cin >> xPts[i] >> yPts[i];

    //sort & set up
    qsort(xPts, points, sizeof(int), cmp);
    qsort(yPts, points, sizeof(int), cmp);
    int *costs = new int[points];

    //calculate x
    costs[0] = 0;
    for (int i = 1; i < points; i++)
        costs[i] = costs[i - 1] + i * (xPts[i] - xPts[i - 1]);
    int xSum = 0;
    for (int i = 0; i < points; i++)
        xSum = (xSum + costs[i]) % MOD;

    //calculate y
    costs[0] = 0;
    for (int i = 1; i < points; i++)
        costs[i] = costs[i - 1] + i * (yPts[i] - yPts[i - 1]);
    int ySum = 0;
    for (int i = 0; i < points; i++)
        ySum = (ySum + costs[i]) % MOD;

    cout << ((xSum + ySum) % MOD) << endl;
}