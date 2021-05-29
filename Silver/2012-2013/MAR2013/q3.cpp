// Start: 8:54
// Think: 9:08
// Write: 9:42
// Debug: 9:46
#include <iostream>
#include <algorithm>
using namespace std;

#define MAX_COWS 1'000
int cost[MAX_COWS][MAX_COWS][2];
#define INF 1'000'000'000

int main(void)
{
    //read
#ifndef HOME
    freopen("cowrun.in", "r", stdin);
    freopen("cowrun.out", "w", stdout);
#endif
    int numCows;
    cin >> numCows;
    int *cows = new int[numCows];
    for (int i = 0; i < numCows; i++)
        cin >> cows[i];

    //sort -> set up
    sort(cows, cows + numCows);
    for (int i = 0; i < numCows; i++)
        for (int j = 0; j < numCows; j++)
            cost[i][j][false] = cost[i][j][true] = INF;

    //fill the DP
    for (int i = 0; i < numCows; i++)
        cost[i][i][false] = cost[i][i][true] = abs(cows[i]) * numCows;
    int currCost, currPos, cowsOn;
    for (int i = 0; i < numCows; i++)         //cows looked at
        for (int j = 0; j < numCows - i; j++) //start cow
            for (int k = 0; k <= 1; k++)      //side
            {
                currCost = cost[j][j + i][k];
                if (currCost == INF)
                    continue;
                currPos = cows[k ? j + i : j];
                cowsOn = numCows - i - 1;
                if (j != 0)
                    cost[j - 1][j + i][false] = min(cost[j - 1][j + i][false], currCost + (currPos - cows[j - 1]) * cowsOn);
                if (j + i < numCows - 1)
                    cost[j][j + i + 1][true] = min(cost[j][j + i + 1][true], currCost + (cows[j + i + 1] - currPos) * cowsOn);
            }

    //print and delete
    cout << min(cost[0][numCows - 1][false], cost[0][numCows - 1][true]) << endl;
    delete[] cows;
    return 0;
}