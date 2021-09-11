// Start: 9:22
// Think: 9:53
// Write: 10:18
// Debug: 10:28
#include <iostream>
using namespace std;

#define MAX_DOOR 7
#define MAX_ROOM 100
long long DP[MAX_ROOM][MAX_DOOR][MAX_ROOM];
#define BIG_NUM 1'000'000'000

int main(void)
{
    //read
#ifndef HOME
    freopen("cbarn2.in", "r", stdin);
    freopen("cbarn2.out", "w", stdout);
#endif
    int numRooms, numDoors;
    cin >> numRooms >> numDoors;
    int *cows = new int[numRooms];
    for (int i = 0; i < numRooms; i++)
        cin >> cows[i];

    //run DP 100x works
    for (int startPos = 0; startPos < numRooms; startPos++)
        for (int pos = numRooms - 1; pos >= startPos; pos--)
            for (int doors = 1; doors <= numDoors; doors++)
            {
                DP[startPos][pos][doors] = BIG_NUM;
                long long cost = 0;
                for (int i = pos + 1; i < numRooms; i++)
                {
                    DP[startPos][pos][doors] = min(DP[startPos][pos][doors],
                                                   cost + DP[startPos][i][doors - 1]);
                    cost += cows[i] * (i - pos);
                }
                for (int i = 0; i < startPos; i++)
                    cost += cows[i] * (numRooms - pos + i);
                if ((doors == 1) || (pos == numRooms - 1))
                    DP[startPos][pos][doors] = cost;
            }

    //print and delete
    long long ans = BIG_NUM;
    for (int i = 0; i < numRooms; i++)
        ans = min(ans, DP[i][i][numDoors]);
    cout << ans << endl;
    delete[] cows;
    return 0;
}