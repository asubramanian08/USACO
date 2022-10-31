// 5:52 - 6:38 - 7:19
// Problem: Only certain indices are reduced by one
#include <iostream>
#include <set>
#include <cassert>
using namespace std;
using pii = pair<int, int>;

int main(void)
{
    // IO Set up
    ios_base::sync_with_stdio(false);
    // cin.tie(nullptr); // not useful
#ifndef HOME
    freopen("boarding.in", "r", stdin);
    freopen("boarding.out", "w", stdout);
#endif

    // Read
    int n, pos[200010], time[200010];
    cin >> n;
    for (int i = 0; i < n; i++)
        cin >> pos[i] >> time[i];
    set<pii> s;
    s.insert({0, 0});

    // Calculate seating time
    int ans = 0, subIndex = 0;
    for (int i = n - 1; i >= 0; i--)
    {
        pii latestLine = *prev(s.lower_bound({pos[i] + subIndex, 0}));
        latestLine.first -= subIndex;
        int curr = latestLine.second + (pos[i] - latestLine.first) + time[i];
        ans = max(ans, curr);
        pii toAdd = {pos[i] + (subIndex++), curr};
        set<pii>::iterator after;
        if (pii before = *prev(s.lower_bound({toAdd.first, 0}));
            toAdd.second <= before.second + (toAdd.first - before.first))
            assert(false);
        while ((after = s.lower_bound({toAdd.first, 0})) != s.end() &&
               (after->second <= toAdd.second + (after->first - toAdd.first)))
            s.erase(after);
        s.insert(toAdd);
    }

    // print
    cout << ans << endl;
    return 0;
}