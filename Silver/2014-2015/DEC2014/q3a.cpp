// Start: 10:14
// Think: 10:20
// Write: 10:29
// Debug: 10:41
#include <iostream>
using namespace std;

int main(void)
{
    // read
#ifndef HOME
    freopen("cowjog.in", "r", stdin);
    freopen("cowjog.out", "w", stdout);
#endif
    long long numCows, endTime;
    cin >> numCows >> endTime;
    using pll = pair<long long, long long>;
    pll *cows = new pll[numCows];
    for (int i = 0; i < numCows; i++)
        cin >> cows[i].first >> cows[i].second;

    // cow endings
    long long *endAt = new long long[numCows];
    for (int i = 0; i < numCows; i++)
        endAt[i] = cows[i].second * endTime + cows[i].first;

    // group cows
    int groups = 1; // the farthest cow
    for (int i = numCows - 2; i >= 0; i--)
    {
        groups += endAt[i] < endAt[i + 1];
        if (endAt[i] > endAt[i + 1])
            endAt[i] = endAt[i + 1];
    }

    // print and delete
    cout << groups << endl;
    delete[] cows;
    delete[] endAt;
    return 0;
}