#include <iostream>
#include <algorithm>
#include <set>
using namespace std;
using pii = pair<long long, long long>;
#define NA -1
#define BIG_NUM 1'000'000'000'000
#define x first
#define y second

long long sqrDist(pii p1, pii p2)
{
    return (p1.x - p2.x) * (p1.x - p2.x) +
           (p1.y - p2.y) * (p1.y - p2.y);
}

int main(void)
{
    // read
    int numPoints;
    cin >> numPoints;
    pii *points = new pii[numPoints];
    for (int i = 0; i < numPoints; i++)
        cin >> points[i].x >> points[i].y;
    sort(points, points + numPoints);

    // linked list of points in order of x
    int *next = new int[numPoints];
    int *prev = new int[numPoints];
    for (int i = 0; i < numPoints; i++)
        next[i] = i + 1, prev[i] = i - 1;
    next[numPoints - 1] = prev[0] = NA;

    // min cost - remove from link list once set
    if (numPoints == 1)
    {
        cout << 0 << endl;
        return 0;
    }
    set<pii> toAdd; // cost, node
    toAdd.insert(pii(0, 0));
    toAdd.insert(pii(BIG_NUM, NA));
    pii *searchTill = new pii[numPoints];
    for (int i = 0; i < numPoints; i++)
        searchTill[i] = pii(NA, NA);
    bool *removed = new bool[numPoints];
    for (int i = 0; i < numPoints; i++)
        removed[i] = false;
    long long totalCost = 0;
    for (int i = 0; i < numPoints; i++)
    {
        // remove it
        pii remove = *toAdd.begin();
        toAdd.erase(remove);
        totalCost += remove.first;
        if (next[remove.second] != NA)
            prev[next[remove.second]] = prev[remove.second];
        if (prev[remove.second] != NA)
            next[prev[remove.second]] = next[remove.second];
        removed[remove.second] = true;
        searchTill[remove.second] = pii(remove.second, remove.second);
        // find all the next positions
        for (int j = 0; j < numPoints; j++)
        {
            if (!removed[j])
                continue;
            long long minCost = toAdd.begin()->first;
            long long curr = next[searchTill[j].second];
            while (curr != NA && sqrDist(points[j], pii(points[curr].x, points[j].y)) <= minCost)
            {
                if (!removed[curr])
                {
                    toAdd.insert(pii(sqrDist(points[j], points[curr]), curr));
                    minCost = toAdd.begin()->first;
                }
                curr = next[curr];
            }
            next[searchTill[j].second] = curr;
            curr = prev[searchTill[j].first];
            while (curr != NA && sqrDist(points[j], pii(points[curr].x, points[j].y)) <= minCost)
            {
                if (!removed[curr])
                {
                    toAdd.insert(pii(sqrDist(points[j], points[curr]), curr));
                    minCost = toAdd.begin()->first;
                }
                curr = prev[curr];
            }
            prev[searchTill[j].first] = curr;
        }
    }

    // print and delete
    cout << totalCost << endl;
    delete[] points;
    delete[] next;
    delete[] prev;
    return 0;
}