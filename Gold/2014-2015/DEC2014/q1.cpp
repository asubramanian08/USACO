// Start: 8:25
// Think: 8:40
// Write: 9:12
// Debug: 9:19
#include <iostream>
using namespace std;

struct cow
{
    int height, weight, strength;
};
using pii = pair<int, int>;
#define NA -1

int main(void)
{
    //read
#ifndef HOME
    freopen("guard.in", "r", stdin);
    freopen("guard.out", "w", stdout);
#endif
    int numCows, mark;
    cin >> numCows >> mark;
    cow *cows = new cow[numCows];
    for (int i = 0; i < numCows; i++)
        cin >> cows[i].height >> cows[i].weight >> cows[i].strength;

    //Bits on in a mask
    int *bitsOn = new int[1 << numCows], on;
    for (int mask = 0; mask < (1 << numCows); mask++)
    {
        for (int i = on = 0; i < numCows; i++)
            if (mask & (1 << i))
                on++;
        bitsOn[mask] = on;
    }

    //DP[mask] = (best safety for a mask, height)
    pii *DP = new pii[1 << numCows];
    DP[0] = pii(NA, 0);
    for (int i = 0; i < numCows; i++)
        DP[1 << i] = pii(cows[i].strength, cows[i].height);
    for (int cowsInStack = 2; cowsInStack <= numCows; cowsInStack++)
        for (int mask = 0; mask < (1 << numCows); mask++)
        {
            if (bitsOn[mask] != cowsInStack)
                continue;
            DP[mask].first = NA;
            for (int i = 0; i < numCows; i++)
                if (mask & (1 << i))
                {
                    DP[mask].second = DP[mask & ~(1 << i)].second + cows[i].height;
                    if (DP[mask & ~(1 << i)].first >= cows[i].height)
                        DP[mask].first = max(DP[mask].first, min(DP[mask & ~(1 << i)].first - cows[i].weight, cows[i].strength));
                }
        }

    //print and delete
    int ans = NA;
    for (int mask = 0; mask < (1 << numCows); mask++)
        if (DP[mask].second >= mark)
            ans = max(ans, DP[mask].first);
    if (ans == NA)
        cout << "Mark is too tall" << endl;
    else
        cout << ans << endl;
    delete[] cows;
    delete[] bitsOn;
    delete[] DP;
    return 0;
}