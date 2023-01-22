// 10:17 - 12:45
#include <iostream>
#include <set>
#include <queue>
#include <algorithm>
using namespace std;
using pii = pair<int, int>;

int main(void)
{
    ios_base::sync_with_stdio(false);
#ifndef HOME
    freopen("trapped.in", "r", stdin);
    freopen("trapped.out", "w", stdout);
#endif
    int n, stuck = 0;
    cin >> n;
    pii *bales = new pii[n];
    for (int i = 0; i < n; i++)
        cin >> bales[i].second >> bales[i].first;
    sort(bales, bales + n);
    set<pair<pii, int>> ranges;
    auto rangeSize = [bales](pair<pii, int> range)
    { return bales[range.first.second].first - bales[range.first.first].first; };
    auto addRange = [&](pair<pii, int> range)
    {
        if (rangeSize(range) <= bales[range.first.first].second &&
            rangeSize(range) <= bales[range.first.second].second)
        {
            stuck += range.second;
            range.second = 0;
        }
        ranges.insert(range);
    };
    for (int i = 1; i < n; i++)
        addRange({{i - 1, i}, bales[i].first - bales[i - 1].first});
    queue<int> checkBale;
    for (int i = 0; i < n; i++)
        checkBale.push(i);
    while (!checkBale.empty())
    {
        int x = checkBale.front();
        checkBale.pop();
        if (ranges.empty() || (x != ranges.rbegin()->first.second && ranges.lower_bound({{x, 0}, 0})->first.first != x))
            continue; // not a valid bale anymore
        if (x == ranges.begin()->first.first)
        {
            if (rangeSize(*ranges.begin()) > bales[x].second)
            {
                ranges.erase(ranges.begin());
                if (!ranges.empty())
                    checkBale.push(ranges.begin()->first.first);
            }
        }
        else if (x == ranges.rbegin()->first.second)
        {
            if (rangeSize(*ranges.rbegin()) > bales[x].second)
            {
                ranges.erase(prev(ranges.end()));
                if (!ranges.empty())
                    checkBale.push(ranges.rbegin()->first.second);
            }
        }
        else
        {
            pair<pii, int> leftRange = *prev(ranges.lower_bound({{x, 0}, 0}));
            pair<pii, int> rightRange = *ranges.lower_bound({{x, 0}, 0});
            if ((leftRange.second == 0 || rangeSize(leftRange) > bales[leftRange.first.second].second) &&
                (rightRange.second == 0 || rangeSize(rightRange) > bales[rightRange.first.first].second))
            {
                ranges.erase(leftRange);
                ranges.erase(rightRange);
                addRange({{leftRange.first.first, rightRange.first.second},
                          leftRange.second + rightRange.second});
                checkBale.push(leftRange.first.first);
                checkBale.push(rightRange.first.second);
            }
        }
    }
    cout << stuck << endl;
    delete[] bales;
    return 0;
}