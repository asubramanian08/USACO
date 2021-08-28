// Start: 10:28
// Think: 10:40
// Write: 10:58
// Debug: 11:01
#include <iostream>
using namespace std;

#define MAX_GAMES 100010
#define MAX_SWITCH 21
struct best
{
    int hoof;
    int paper;
    int scissor;
};
best DP[MAX_GAMES][MAX_SWITCH];
#define NA -1

int main(void)
{
    //read
#ifndef HOME
    freopen("hps.in", "r", stdin);
    freopen("hps.out", "w", stdout);
#endif
    int numGames, numSwitch;
    cin >> numGames >> numSwitch;
    char *games = new char[numGames];
    for (int i = 0; i < numGames; i++)
        cin >> games[i];
    numSwitch++;

    //set base
    for (int i = 0; i < numSwitch; i++)
        DP[numGames][i].hoof = DP[numGames][i].paper = DP[numGames][i].scissor = 0;

    //run the DP
    for (int i = numGames - 1; i >= 0; i--)
        for (int j = 0; j <= numSwitch; j++)
        {
            if (j == 0)
            {
                DP[i][j].hoof = DP[i][j].scissor = DP[i][j].scissor = NA;
                continue;
            }
            DP[i][j].hoof = DP[i + 1][j].hoof;
            DP[i][j].paper = DP[i + 1][j].paper;
            DP[i][j].scissor = DP[i + 1][j].scissor;
            int theirBest = max(DP[i + 1][j - 1].hoof, max(DP[i + 1][j - 1].paper, DP[i + 1][j - 1].scissor));
            if (games[i] == 'H')
                DP[i][j].hoof = max(DP[i][j].hoof + 1, theirBest + 1);
            else if (games[i] == 'P')
                DP[i][j].paper = max(DP[i][j].paper + 1, theirBest + 1);
            else
                DP[i][j].scissor = max(DP[i][j].scissor + 1, theirBest + 1);
        }

    //print and delete
    int ans = max(DP[0][numSwitch].hoof, max(DP[0][numSwitch].paper, DP[0][numSwitch].scissor));
    cout << ans << endl;
    delete[] games;
    return 0;
}