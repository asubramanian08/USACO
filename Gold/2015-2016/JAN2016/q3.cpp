// Start: 10:12
// Think: 10:52,
// Write:
// Debug:
// After looking at sol: 10:23-11:28
#include <iostream>
#include <vector>
#include <set>
using namespace std;

using pii = pair<long long, long long>;
long long orient(pii p1, pii p2, pii p3)
{
    return (p2.first - p1.first) * (p3.second - p1.second) -
           (p2.second - p1.second) * (p3.first - p1.first);
}

int main(void)
{
    // read
#ifndef HOME
    freopen("lightsout.in", "r", stdin);
    freopen("lightsout.out", "w", stdout);
#endif
    int numVertices;
    cin >> numVertices;
    pii *vertices = new pii[numVertices];
    for (int i = 0; i < numVertices; i++)
        cin >> vertices[i].first >> vertices[i].second;

    /** Compare list:
     * 0 = exit
     * -1 = clockwise
     * -2 = counter-clockwise
     * any other # = length of side */
    vector<int> compareList = {0};
    for (int i = 0; i < numVertices; i++)
    {
        int j = (i + 1) % numVertices;
        int k = (i + 2) % numVertices;
        compareList.push_back(abs(vertices[j].first - vertices[i].first) +
                              abs(vertices[j].second - vertices[i].second));
        compareList.push_back(orient(vertices[i], vertices[j], vertices[k]) < 0 ? -1 : -2);
    }
    compareList.back() = 0;

    // regular cost (lights on)
    int *regular = new int[numVertices + 1];
    regular[0] = 0;
    for (int i = 1; i < numVertices; i++)
        regular[i] = regular[i - 1] + compareList[i * 2 - 1];
    regular[numVertices] = 0;
    for (int i = numVertices - 1; i >= 0; i--)
        regular[i] = min(regular[i], regular[i + 1] + compareList[i * 2 + 1]);

    // first unique prefix
    multiset<vector<int>> prefixes;
    for (int start = 0; start < compareList.size(); start += 2)
        for (int end = start + 1; end <= compareList.size(); end += 2)
            prefixes.insert(vector<int>(compareList.begin() + start, compareList.begin() + end));
    int ans = 0, curr, end;
    for (int start = 2; start + 2 < compareList.size(); start += 2)
    {
        curr = 0;
        for (end = start + 1; end <= compareList.size(); end += 2)
            if (prefixes.count(vector<int>(compareList.begin() + start, compareList.begin() + end)) == 1)
                break;
            else
                curr += compareList[end];
        ans = max(ans, curr + regular[end / 2] - regular[start / 2]);
    }

    // print and delete
    cout << ans << endl;
    delete[] vertices;
    delete[] regular;
    return 0;
}