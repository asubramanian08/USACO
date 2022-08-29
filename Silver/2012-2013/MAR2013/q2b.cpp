// 12:20 - 12:46
#include <iostream>
#include <algorithm>
#include <set>
using namespace std;
using pii = pair<int, int>;

int main(void)
{
#ifndef HOME
    freopen("painting.in", "r", stdin);
    freopen("painting.out", "w", stdout);
#endif
    int n, rect[50'010][4];
    pii points[100'020];
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> rect[i][0] >> rect[i][1] >> rect[i][2] >> rect[i][3];
        points[2 * i + 0] = pii(rect[i][0], i);
        points[2 * i + 1] = pii(rect[i][2], i);
    }
    sort(points, points + 2 * n);
    int ans = 0;
    set<pii> yRange;
    for (int i = 0; i < 2 * n; i++)
    {
        int r = points[i].second;
        pii newPoint(rect[r][1], rect[r][3]);
        if (points[i].first == rect[r][0])
        {
            auto itr = yRange.upper_bound(newPoint);
            if (!yRange.empty())
                itr--;
            if (itr != yRange.end() && rect[itr->second][3] > rect[r][3])
                continue;
            yRange.insert(newPoint);
            ans++;
        }
        else if (yRange.find(newPoint) != yRange.end())
            yRange.erase(newPoint);
    }
    cout << ans << endl;
}