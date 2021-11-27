// convex hull
using pii = pair<long long, long long>;
long long orient(pii p1, pii p2, pii p3)
{
    return (p2.first - p1.first) * (p3.second - p1.second) -
           (p2.second - p1.second) * (p3.first - p1.first);
}
vector<pii> upper_hull(pii *stones, int numStones)
{
    vector<pii> hull = {stones[0], stones[1]};
    for (int i = 2; i < numStones; i++)
    {
        while (hull.size() > 1 && orient(hull[hull.size() - 2], hull[hull.size() - 1], stones[i]) >= 0)
            hull.pop_back();
        hull.push_back(stones[i]);
    }
    return hull;
}
vector<pii> lower_hull(pii *stones, int numStones)
{
    vector<pii> hull = {stones[0], stones[1]};
    for (int i = 2; i < numStones; i++)
    {
        while (hull.size() > 1 && orient(hull[hull.size() - 2], hull[hull.size() - 1], stones[i]) <= 0)
            hull.pop_back();
        hull.push_back(stones[i]);
    }
    return hull;
}