// 11:04 - 11:57
#include <iostream>
#include <algorithm>
using namespace std;
#define X 2019201913
#define Y 2019201949
#define MOD 2019201997
#define MAX_N 7500

int main(void)
{
    ios_base::sync_with_stdio(false);
#ifndef HOME
    freopen("walk.in", "r", stdin);
    freopen("walk.out", "w", stdout);
#endif
    int n, k;
    cin >> n >> k;
    auto willingToWalk = [](int i, int j)
    {
        long long x = min(i, j) + 1, y = max(i, j) + 1;
        return (X * x + Y * y) % MOD;
    };
    bool vis[MAX_N] = {false};
    long long dist[MAX_N] = {0};
    for (int i = 1; i < n; i++)
        dist[i] = MOD;
    for (int i = 0; i < n; i++)
    {
        int toAdd = -1;
        for (int j = 0; j < n; j++)
            if (!vis[j] && (toAdd == -1 || dist[j] < dist[toAdd]))
                toAdd = j;
        vis[toAdd] = true;
        for (int j = 0; j < n; j++)
            if (!vis[j])
                dist[j] = min(dist[j], willingToWalk(toAdd, j));
    }
    sort(dist, dist + n);
    cout << dist[n - k + 1] << endl;
    return 0;
}