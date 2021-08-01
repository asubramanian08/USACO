// Start: 9:30
// Think: 10:03
// Write: 10:35
// Debug: 11:16
#include <iostream>
#include <string>
using namespace std;

#define MAX_BUT 26
int convert[MAX_BUT][MAX_BUT];
#define MAX_COMB 100010
int cost[MAX_COMB][MAX_BUT];
int best[MAX_COMB][MAX_BUT];
#define BIG_NUM 1000000000

int main(void)
{
    //read
#ifndef HOME
    freopen("cowmbat.in", "r", stdin);
    freopen("cowmbat.out", "w", stdout);
#endif
    int comboLen, numButs, minStreak;
    cin >> comboLen >> numButs >> minStreak;
    string combo;
    cin >> combo;
    for (int i = 0; i < numButs; i++)
        for (int j = 0; j < numButs; j++)
            cin >> convert[i][j];

    //correct the convert
    for (int i = 0; i < numButs; i++)
        for (int j = 0; j < numButs; j++)
            for (int k = 0; k < numButs; k++)
                if (convert[j][k] > convert[j][i] + convert[i][k])
                    convert[j][k] = convert[j][i] + convert[i][k];

    //set all the costs
    for (int i = 0; i < numButs; i++)
        cost[comboLen][i] = 0;
    for (int i = comboLen - 1; i >= 0; i--)
        for (int j = 0; j < numButs; j++)
            cost[i][j] = cost[i + 1][j] + convert[combo[i] - 'a'][j];

    //find the best
    int theirBest;
    for (int i = comboLen - minStreak; i >= 0; i--)
    {
        for (int j = 0; j < numButs; j++)
            best[i][j] = cost[i][j];
        if (i < comboLen - minStreak)
            for (int j = 0; j < numButs; j++)
                if (best[i][j] > convert[combo[i] - 'a'][j] + best[i + 1][j])
                    best[i][j] = convert[combo[i] - 'a'][j] + best[i + 1][j];
        if (i <= comboLen - 2 * minStreak)
        {
            theirBest = BIG_NUM;
            for (int j = 0; j < numButs; j++)
                theirBest = min(theirBest, best[i + minStreak][j]);
            for (int j = 0; j < numButs; j++)
            {
                int pot = cost[i][j] - cost[i + minStreak][j] + theirBest;
                if (best[i][j] > pot)
                    best[i][j] = pot;
            }
        }
    }

    //print
    int minChange = BIG_NUM;
    for (int i = 0; i < numButs; i++)
        minChange = min(minChange, best[0][i]);
    cout << minChange << endl;
    return 0;
}