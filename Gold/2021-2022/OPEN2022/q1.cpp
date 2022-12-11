// Unofficial: 3:38 - 4:58
#include <iostream>
#include <set>
#include <vector>
#include <algorithm>
using namespace std;

int main(void)
{
    int n, type, time, loc, quant;
    cin >> n;
    vector<pair<pair<int, int>, int>> cows, apples;
    for (int i = 0; i < n; i++)
    {
        cin >> type >> time >> loc >> quant;
        if (type == 1)
            cows.push_back({{time - loc, time + loc}, quant});
        else
            apples.push_back({{time - loc, time + loc}, quant});
    }
    sort(cows.begin(), cows.end());
    sort(apples.begin(), apples.end());
    multiset<pair<int, int>> active;
    long long ans = 0, j = 0;
    for (int i = 0; i < apples.size(); i++)
    {
        while (j < cows.size() && cows[j].first.first <= apples[i].first.first)
            active.insert({cows[j].first.second, cows[j].second}), j++;
        while (apples[i].second != 0)
        {
            auto it = active.lower_bound({apples[i].first.second + 1, 0});
            if (it == active.begin() || active.empty())
                break;
            it--;
            pair<int, int> elem = *it;
            active.erase(it);
            int change = min(elem.second, apples[i].second);
            apples[i].second -= change;
            elem.second -= change;
            ans += change;
            if (elem.second > 0)
                active.insert({elem.first, elem.second});
        }
    }
    cout << ans << endl;
    return 0;
}