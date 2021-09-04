// Start: 9:20
// Think: 9:27
// Write: 9:41
// Debug: 10:03
#include <iostream>
#include <algorithm>
#include <math.h>
using namespace std;

#define MAX_CORD 25010
using pii = pair<int, int>;

int numCows;
pii *cows;
bool *vis;
int maxDist;
void DFS(int cow)
{
    if (vis[cow])
        return;
    vis[cow] = true;
    for (int i = 0; i < numCows; i++)
        if ((cows[cow].first - cows[i].first) * (cows[cow].first - cows[i].first) +
                (cows[cow].second - cows[i].second) * (cows[cow].second - cows[i].second) <=
            maxDist)
            DFS(i);
}
bool canTalk()
{
    fill(vis, vis + numCows, false);
    DFS(0); //any way works
    return all_of(vis, vis + numCows, [](bool val)
                  { return val; });
}

int main(void)
{
    //read
#ifndef HOME
    freopen("moocast.in", "r", stdin);
    freopen("moocast.out", "w", stdout);
#endif
    cin >> numCows;
    cows = new pii[numCows];
    for (int i = 0; i < numCows; i++)
        cin >> cows[i].first >> cows[i].second;

    //bsearch x(cost)
    int hi = MAX_CORD * MAX_CORD;
    int lo = 0;
    vis = new bool[numCows];
    while (hi - lo > 1)
    {
        maxDist = (lo + hi) / 2;
        if (canTalk())
            hi = maxDist;
        else
            lo = maxDist;
    }
    int ans = hi;

    //print and delete
    cout << ans << endl;
    delete[] cows;
    delete[] vis;
    return 0;
}