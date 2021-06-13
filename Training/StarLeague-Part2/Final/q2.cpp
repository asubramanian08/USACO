#include <iostream>
#include <cstring>
#include <algorithm>
using namespace std;

struct point
{
    int x, y;
};
bool cmpX(point &p1, point &p2)
{
    if (p1.x == p2.x)
        return p1.y < p2.y;
    return p1.x < p2.x;
}
bool cmpY(point &p1, point &p2)
{
    if (p1.y == p2.y)
        return p1.x < p2.x;
    return p1.y < p2.y;
}
int maxSect(int sect_pts[4])
{
    int maxSect = sect_pts[0];
    for (int i = 0; i < 4; i++)
        maxSect = max(maxSect, sect_pts[i]);
    return maxSect;
}

int main(void)
{
    //read
    FILE *junk;
    junk = freopen("balancing.in", "r", stdin);
    junk = freopen("balancing.out", "w", stdout);
    int numPoints;
    cin >> numPoints;
    point *by_x = new point[numPoints];
    for (int i = 0; i < numPoints; i++)
        cin >> by_x[i].x >> by_x[i].y;

    //complete by_x and by_y
    sort(&by_x[0], &by_x[numPoints], cmpX);
    point *by_y = new point[numPoints];
    memcpy(by_y, by_x, sizeof(point) * numPoints);
    sort(&by_y[0], &by_y[numPoints], cmpY);

    //do the 2 sweep lines (simultaneous)
    int sect_pts[4] = {0, 0, 0, numPoints}; //tl, tr, ll, lr
    int minSect = maxSect(sect_pts);
    bool afterLine;
    for (int i = 0; i < numPoints; i++)
    {
        //move the sweep line
        sect_pts[3]--;
        sect_pts[2]++;
        if ((i != numPoints - 1) && (by_x[i].x == by_x[i + 1].x))
            continue; //multipule points on same line
        for (int j = 0; j < numPoints; j++)
        {
            //move the sweep line
            afterLine = by_y[j].x > by_x[i].x;
            sect_pts[2 + afterLine]--;
            sect_pts[0 + afterLine]++;
            if ((j != numPoints - 1) && (by_y[j].y == by_y[j + 1].y))
                continue; //multipule points on same line
            //change minSect
            minSect = min(minSect, maxSect(sect_pts));
        }
        //put values back
        sect_pts[3] += sect_pts[1];
        sect_pts[2] += sect_pts[0];
        sect_pts[1] = 0;
        sect_pts[0] = 0;
    }

    //delete and print
    delete[] by_x;
    delete[] by_y;
    cout << minSect;
    return 0;
}