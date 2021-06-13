//~ Skyline problem
#include <iostream>
#include <algorithm>
#include <set>
using namespace std;

struct corner
{
    int x, height;
    bool is_start;
};
bool cmp(corner &c1, corner &c2)
{
    if (c1.x != c2.x)
        return c1.x < c2.x;
    if (c1.is_start != c2.is_start)
        return !c1.is_start;
    return c1.height < c2.height;
}

int main(void)
{
    //read
    FILE *junk;
    junk = freopen("horizon.in", "r", stdin);
    junk = freopen("horizon.out", "w", stdout);
    int numBuild;
    cin >> numBuild;
    corner *corners = new corner[numBuild * 2];
    int x1, x2, height;
    for (int i = 0; i < numBuild; i++)
    {
        cin >> x1 >> x2 >> height;
        corners[i * 2] = {x1, height, true};
        corners[i * 2 + 1] = {x2, height, false};
    }

    //solve (multiset) + print
    sort(&corners[0], &corners[numBuild * 2], cmp);
    multiset<int> currRects;
    currRects.insert(0); //bottem line
    int lastPoint = 0, maxY = 0;
    long long area = 0;
    for (int i = 0; i < numBuild * 2; i++)
    {
        if (corners[i].is_start)
            currRects.insert(corners[i].height);
        else
            currRects.erase(currRects.find(corners[i].height));
        if (maxY != *currRects.rbegin())
        {
            area += ((long long)corners[i].x - lastPoint) * (long long)maxY;
            maxY = *(currRects.rbegin());
            lastPoint = corners[i].x;
        }
    }
    cout << area;
    return 0;
}