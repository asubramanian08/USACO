// Start: 8:35
// Think: 8:52
// Write: 9:15
// Debug: 9:22
#include <iostream>
#include <queue>
using namespace std;

#define NA -1

int main(void)
{
    //read
#ifndef HOME
    freopen("cbarn.in", "r", stdin);
    freopen("cbarn.out", "w", stdout);
#endif
    int numCows;
    cin >> numCows;
    int *cows = new int[numCows];
    for (int i = 0; i < numCows; i++)
        cin >> cows[i];

    //first run: form queue, init pos
    queue<int> looking;
    int *pos = new int[numCows];
    for (int i = 0; i < numCows; i++)
        pos[i] = NA;
    long long ans = 0;
    for (int i = 0; i < numCows; i++)
    {
        for (int j = 0; j < cows[i]; j++)
            looking.push(i);
        if (looking.empty())
            continue;
        pos[i] = looking.front();
        ans += (i - looking.front()) * (i - looking.front());
        looking.pop();
    }

    //second run: set pos -can move others
    for (int i = 0; i < numCows && !looking.empty(); i++)
    {
        if (pos[i] != NA)
        {
            ans -= (i - pos[i]) * (i - pos[i]);
            looking.push(pos[i]);
        }
        pos[i] = looking.front();
        if (looking.front() < i)
            ans += (i - looking.front()) * (i - looking.front());
        else
            ans += (numCows - looking.front() + i) * (numCows - looking.front() + i);
        looking.pop();
    }

    //print and delete
    cout << ans << endl;
    delete[] cows;
    delete[] pos;
    return 0;
}