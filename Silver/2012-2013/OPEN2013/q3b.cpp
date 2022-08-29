// 6:18 - 6:48
#include <iostream>
using namespace std;
using pii = pair<int, int>;

int main(void)
{
#ifndef HOME
    freopen("cruise.in", "r", stdin);
    freopen("cruise.out", "w", stdout);
#endif
    int n, m, k;
    cin >> n >> m >> k;
    pii *graph = new pii[n];
    for (int i = 0; i < n; i++)
        cin >> graph[i].first >> graph[i].second;
    int *vis = new int[n];
    for (int i = 0; i < n; i++)
        vis[i] = -1;
    char *ins = new char[m];
    for (int i = 0; i < m; i++)
        cin >> ins[i];
    vis[0] = 0;
    int curr = 0, itr;
    for (itr = 0; itr < k; itr++)
    {
        for (int i = 0; i < m; i++)
            curr = (ins[i] == 'L' ? graph[curr].first : graph[curr].second) - 1;
        if (vis[curr] != -1)
            break;
        vis[curr] = itr + 1;
    }
    if (itr == k)
        cout << (curr + 1) << endl;
    else
    {
        k -= vis[curr];
        int cycleLen = itr - vis[curr] + 1;
        int moreMoves = k % cycleLen;
        int toFind = vis[curr] + moreMoves;
        int ans = -1;
        for (int i = 0; i < n && ans == -1; i++)
            if (vis[i] == toFind)
                ans = i + 1;
        cout << ans << endl;
    }
}