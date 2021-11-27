// Start: 8:30
// Think: 8:34
// Write: 9:02
// Debug: 9:37
#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

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

int score(pii *team, const vector<pii> &uHull, const vector<pii> &lHull, int numStones)
{
    int total = 0;
    for (int i = 0; i < numStones; i++)
    {
        auto uPos = upper_bound(uHull.begin(), uHull.end(), team[i]);
        if (team[i].first == uHull.back().first)
            uPos = uHull.end() - 1;
        if (uPos == uHull.end() || uPos == uHull.begin() ||
            orient(*(uPos - 1), *uPos, team[i]) > 0 ||
            team[i].second > max((uPos - 1)->second, uPos->second))
            continue;
        auto lPos = upper_bound(lHull.begin(), lHull.end(), team[i]);
        if (team[i].first == lHull.back().first)
            lPos = uHull.end() - 1;
        if (lPos == uHull.end() || lPos == uHull.begin() ||
            orient(*(lPos - 1), *lPos, team[i]) < 0 ||
            team[i].second < min((lPos - 1)->second, lPos->second))
            continue;
        total++;
    }
    return total;
}

int main(void)
{
    // read
#ifndef HOME
    freopen("curling.in", "r", stdin);
    freopen("curling.out", "w", stdout);
#endif
    int numStones;
    cin >> numStones;
    pii *teamA = new pii[numStones];
    for (int i = 0; i < numStones; i++)
        cin >> teamA[i].first >> teamA[i].second;
    pii *teamB = new pii[numStones];
    for (int i = 0; i < numStones; i++)
        cin >> teamB[i].first >> teamB[i].second;

    // convex hulls
    sort(teamA, teamA + numStones);
    vector<pii> uHullA = upper_hull(teamA, numStones);
    vector<pii> lHullA = lower_hull(teamA, numStones);
    sort(teamB, teamB + numStones);
    vector<pii> uHullB = upper_hull(teamB, numStones);
    vector<pii> lHullB = lower_hull(teamB, numStones);

    // team score
    int scoreA = score(teamB, uHullA, lHullA, numStones);
    int scoreB = score(teamA, uHullB, lHullB, numStones);

    // print and delete
    cout << scoreA << ' ' << scoreB << endl;
    delete[] teamA;
    delete[] teamB;
    return 0;
}