// Start: 7:57
// Think: 8:39
// Write: 9:27
// Debug: 9:55
#include <iostream>
#include <vector>
using namespace std;

#define RANGE 1001
using pii = pair<int, int>;
pii ps_2D[RANGE + 1][RANGE + 1];
#define NA -1

pii operator-(pii p1, pii p2) { return pii(p1.first - p2.first, p1.second - p2.second); }
pii operator+(pii p1, pii p2) { return pii(p1.first + p2.first, p1.second + p2.second); }
int query2D(int startX, int endX, int startY, int endY)
{
    pii value = ps_2D[startX][startY] - ps_2D[endX + 1][startY] -
                ps_2D[startX][endY + 1] + ps_2D[endX + 1][endY + 1];
    return value.second != 0 ? NA : value.first;
}
int guernseyBound(int xPos, int extremeX, int startY, int endY)
{
    int lo = xPos, hi = extremeX;
    if (query2D(min(lo, hi), max(lo, hi), startY, endY) != NA)
        return hi;
    while (abs(hi - lo) > 1)
        if (query2D(min(lo, (lo + hi) / 2), max(lo, (lo + hi) / 2), startY, endY) == NA)
            hi = (lo + hi) / 2;
        else
            lo = (lo + hi) / 2;
    return lo;
}
int reduceArea(int changeX, int boundX, int startY, int endY)
{
    int lo = changeX, hi = boundX, cowsIn = query2D(min(lo, hi), max(lo, hi), startY, endY);
    if (query2D(hi, hi, startY, endY) == cowsIn)
        return hi;
    while (abs(hi - lo) > 1)
        if (query2D(min((lo + hi) / 2, boundX), max((lo + hi) / 2, boundX), startY, endY) == cowsIn)
            lo = (lo + hi) / 2;
        else
            hi = (lo + hi) / 2;
    return lo;
}

int main(void)
{
    //set ps_2D
    for (int i = 0; i <= RANGE; i++)
        for (int j = 0; j <= RANGE; j++)
            ps_2D[i][j] = pii(0, 0);

    //read
#ifndef HOME
    freopen("cowrect.in", "r", stdin);
    freopen("cowrect.out", "w", stdout);
#endif
    int numCows;
    cin >> numCows;
    vector<pii> holsteins;
    for (int i = 0; i < numCows; i++)
    {
        int x, y;
        char breed;
        cin >> x >> y >> breed;
        if (breed == 'H')
            holsteins.push_back(pii(x, y));
        ps_2D[x][y] = breed == 'H' ? pii(1, 0) : pii(0, 1);
    }

    //2D prefix sum
    for (int i = 1; i <= RANGE; i++)
    {
        ps_2D[RANGE][i] = ps_2D[RANGE][i] + ps_2D[RANGE][i - 1];
        ps_2D[i][RANGE] = ps_2D[i][RANGE] + ps_2D[i - 1][RANGE];
    }
    for (int i = RANGE - 1; i >= 0; i--)
        for (int j = RANGE - 1; j >= 0; j--)
            ps_2D[i][j] = ps_2D[i][j] + ps_2D[i][j + 1] + ps_2D[i + 1][j] - ps_2D[i + 1][j + 1];

    //MaxCows, Area: 2 cows --> expand width
    int maxCows = 1, area = 0;
    for (int i = 0; i < holsteins.size(); i++)
        for (int j = 0; j < holsteins.size(); j++)
        {
            //set up
            int startX = min(holsteins[i].first, holsteins[j].first),
                endX = max(holsteins[i].first, holsteins[j].first),
                startY = min(holsteins[i].second, holsteins[j].second),
                endY = max(holsteins[i].second, holsteins[j].second);
            if (query2D(startX, endX, startY, endY) == NA)
                continue;
            //startX
            startX = guernseyBound(startX, 0, startY, endY);
            startX = reduceArea(startX, endX, startY, endY);
            //endX
            endX = guernseyBound(endX, RANGE - 1, startY, endY);
            endX = reduceArea(endX, startX, startY, endY);
            //update answer
            int currCows = query2D(startX, endX, startY, endY);
            int currArea = (endX - startX) * (endY - startY);
            if (currCows > maxCows)
            {
                maxCows = currCows;
                area = currArea;
            }
            else if (currCows == maxCows)
                area = min(area, currArea);
        }

    //print
    cout << maxCows << endl
         << area << endl;
    return 0;
}