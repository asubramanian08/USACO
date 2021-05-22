// Start: 12:20
// Think: 12:39
// Write: 12:50
// Debug: 12:58 -> cout printing
#include <iostream>
#include <algorithm>
using namespace std;

#define BIG_NUM 1'000'000'000

int main(void)
{
    //read
#ifndef HOME
    freopen("wifi.in", "r", stdin);
    freopen("wifi.out", "w", stdout);
#endif
    int numCows;
    double A, B;
    cin >> numCows >> A >> B;
    double *cowPos = new double[numCows];
    for (int i = 0; i < numCows; i++)
        cin >> cowPos[i];

    //set up
    sort(cowPos, cowPos + numCows);
    double *cost = new double[numCows];
    for (int i = 0; i < numCows; i++)
        cost[i] = BIG_NUM;

    //run algo with 1D DP
    for (int i = numCows - 1; i >= 0; i--)
        for (int j = i; j < numCows; j++)
            cost[i] = min(cost[i], A + B * (cowPos[j] - cowPos[i]) / 2 + (j == numCows - 1 ? 0 : cost[j + 1]));

    //print and delete
    cout.precision(17);
    cout << cost[0] << endl;
    delete[] cowPos;
    delete[] cost;
    return 0;
}