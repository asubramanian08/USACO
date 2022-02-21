// Start: ?
// Think: 10:00, 10:27-10:50
// Write: 11:26
// Debug: 11:27 (6/20)
#include <iostream>
#include <algorithm>
using namespace std;

using pll = pair<long long, long long>;
long long orient(pll p1, pll p2, pll p3)
{
    return (p2.first - p1.first) * (p3.second - p1.second) -
           (p2.second - p1.second) * (p3.first - p1.first);
}
bool inside_tri(pll t1, pll t2, pll t3, pll pt)
{
    return ((orient(t1, t2, pt) < 0) == (orient(t2, t3, pt) < 0)) &&
           ((orient(t2, t3, pt) < 0) == (orient(t3, t1, pt) < 0));
}

int main(void)
{
    int numNodes;
    cin >> numNodes;
    pll *points = new pll[numNodes];
    for (int i = 0; i < numNodes; i++)
        cin >> points[i].first >> points[i].second;
    int *perm = new int[numNodes];
    int fact = 1, ans = 0;
    for (int i = 0; i < numNodes; i++)
        perm[i] = i, fact *= (i + 1);
    for (int i = 0; i < fact; i++)
    {
        pll p1 = points[perm[0]], p2 = points[perm[1]], p3 = points[perm[2]];
        bool works = true;
        for (int j = 3; j < numNodes && works; j++)
            if (inside_tri(p1, p2, points[perm[j]], p3))
                p3 = points[perm[j]];
            else if (inside_tri(p1, points[perm[j]], p3, p2))
                p2 = points[perm[j]];
            else if (inside_tri(points[perm[j]], p2, p3, p1))
                p1 = points[perm[j]];
            else if (!inside_tri(p1, p2, p3, points[perm[j]]))
                works = false;
        ans += works;
        next_permutation(perm, perm + numNodes);
    }
    cout << ans << endl;
    delete[] points;
    delete[] perm;
    return 0;
}