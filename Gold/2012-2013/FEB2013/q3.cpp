// 4:02 - 4:45
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int maxPath(vector<int> l, vector<int> r, vector<vector<int>> lConns)
{
    vector<int> rScore(r);
    int ans = 0, curr;
    for (int i = 0; i < l.size(); i++)
    {
        curr = l[i];
        for (int j = 0; j < lConns[i].size(); j++)
        {
            int conn = lConns[i][j], fromValue = rScore[conn] + l[i];
            rScore[conn] = max(rScore[conn], curr + r[conn]);
            curr = max(curr, fromValue);
        }
        ans = max(ans, curr);
    }
    for (int i = 0; i < rScore.size(); i++)
        ans = max(ans, rScore[i]);
    return ans;
}

int main(void)
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
#ifndef HOME
    freopen("route.in", "r", stdin);
    freopen("route.out", "w", stdout);
#endif
    int n, m, R;
    cin >> n >> m >> R;
    vector<int> left(n), right(m);
    for (int i = 0; i < n; i++)
        cin >> left[i];
    for (int i = 0; i < m; i++)
        cin >> right[i];
    vector<vector<int>> lConns(n), rConns(m);
    for (int i = 0; i < R; i++)
    {
        int l, r;
        cin >> l >> r;
        l--, r--;
        lConns[l].push_back(r);
        rConns[r].push_back(l);
    }
    for (int i = 0; i < n; i++)
        sort(lConns[i].begin(), lConns[i].end());
    for (int i = 0; i < m; i++)
        sort(rConns[i].begin(), rConns[i].end());
    int ans = max(maxPath(left, right, lConns),
                  /* maxPath(right, left, rConns)*/ 0);
    cout << ans << endl;
    return 0;
}