// Official: Incorrect
#include <iostream>
#include <set>
using namespace std;

int main(void)
{
    ios_base::sync_with_stdio(false);
    int n, mount[2010], q, idx, change;
    cin >> n;
    for (int i = 0; i < n; i++)
        cin >> mount[i];
    auto slope = [&](int m1, int m2)
    { return ((double)mount[m2] - mount[m1]) / (m2 - m1); };
    set<pair<double, int>> view[2010];
    for (int i = 0; i < n - 1; i++)
        for (int j = i + 1; j < n; j++)
            if (view[i].empty() || slope(i, j) >= view[i].rbegin()->first)
                view[i].insert({slope(i, j), j});
    cin >> q;
    while (q--)
    {
        cin >> idx >> change;
        mount[--idx] += change;
        for (int i = 0; i < idx; i++)
        {
            mount[idx] -= change;
            view[i].erase({slope(i, idx), idx});
            mount[idx] += change;
            double s = slope(i, idx);
            pair<double, int> search = {s, idx};
            if (auto it = view[i].lower_bound(search); it == view[i].end() || it->second > idx)
            {
                while (true)
                {
                    it = view[i].lower_bound(search);
                    if (it == view[i].begin() || (it = prev(it))->second < idx)
                        break;
                    view[i].erase(it);
                }
                view[i].insert(search);
            }
        }
        view[idx].clear();
        for (int j = idx + 1; j < n; j++)
            if (view[idx].empty() || slope(idx, j) >= view[idx].rbegin()->first)
                view[idx].insert({slope(idx, j), j});
        int ans = 0;
        for (int i = 0; i < n; i++)
            ans += view[i].size();
        cout << ans << endl;
    }
    return 0;
}