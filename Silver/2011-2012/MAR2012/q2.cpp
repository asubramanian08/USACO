// Start: 3:24
// Think: 3:31
// Write: 3:49
// Debug: 3:59
//Sweep line
#include <iostream>
#include <set>
using namespace std;

typedef pair<int, int> drop;
#define BIG_NUM 10000000

int main(void)
{
    //read
#ifndef HOME
    freopen("fpot.in", "r", stdin);
    freopen("fpot.out", "w", stdout);
#endif
    int numDrops, dist;
    cin >> numDrops >> dist;
    drop *drops = new drop[numDrops];
    for (int i = 0; i < numDrops; i++)
        cin >> drops[i].first >> drops[i].second;

    //prep
    sort(drops, drops + numDrops, [](const drop &d1, const drop &d2) { return d1.second < d2.second; });
    set<int> widths;
    int start, minDist = BIG_NUM, upTill = numDrops - 1, closest;
    for (start = upTill; (start >= 0) && (drops[upTill].second - drops[start].second < dist); start--)
        ;

    //sweep line
    for (int i = start; i >= 0; i--)
    {
        while (drops[upTill].second - drops[i].second >= dist)
        {
            widths.insert(drops[upTill].first);
            upTill--;
        }
        auto pos = widths.lower_bound(drops[i].first);
        if (pos != widths.end())
            minDist = min(minDist, *pos - drops[i].first);
        if (pos != widths.begin())
        {
            pos--;
            minDist = min(minDist, drops[i].first - *pos);
        }
    }

    //print and delete
    if (minDist == BIG_NUM)
        cout << "-1";
    else
        cout << minDist;
    delete[] drops;
    return 0;
}