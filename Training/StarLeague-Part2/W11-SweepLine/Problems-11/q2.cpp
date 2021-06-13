#include <iostream>
#include <algorithm>
#include <set>
using namespace std;

#define BIG_NUM 1000000000000000
typedef pair<int, int> point;
#define x first
#define y second
typedef unsigned long long ull;

ull bigRect(int numPoints, point *points)
{
    ull maxX = points[0].x, maxY = points[0].y,
        minX = points[0].x, minY = points[0].y;
    for (int i = 1; i < numPoints; i++)
    {
        if (points[i].x < minX)
            minX = points[i].x;
        else if (points[i].x > maxX)
            maxX = points[i].x;
        if (points[i].y < minY)
            minY = points[i].y;
        else if (points[i].y > maxY)
            maxY = points[i].y;
    }
    return (maxX - minX) * (maxY - minY);
}
ull xRect(int numPoints, point *points)
{
    sort(&points[0], &points[numPoints]); //x then y
    //add the y's to set
    multiset<int> ys;
    for (int i = 0; i < numPoints; i++)
        ys.insert(points[i].y);
    //loop through by x (cuts points in half) -> enclose both halves
    int minY = points[0].y, maxY = points[0].y;
    ull minArea = BIG_NUM, arr1, arr2;
    for (int i = 0; i < numPoints - 1; i++)
    {
        //handle y ...
        ys.erase(ys.find(points[i].y));
        if (points[i].y < minY)
            minY = points[i].y;
        else if (points[i].y > maxY)
            maxY = points[i].y;
        if (points[i].x == points[i + 1].x)
            continue;
        //find 2 halves areas and change minArea
        arr1 = (ull)(points[i].x - points[0].x) * (ull)(maxY - minY);
        arr2 = (ull)(points[numPoints - 1].x - points[i + 1].x) *
               (ull)((*ys.rbegin()) - (*ys.begin()));
        minArea = min(minArea, arr1 + arr2);
    }
    return minArea;
}
bool cmpY(point &p1, point &p2)
{
    if (p1.y != p2.y)
        return p1.y < p2.y;
    return p1.x < p2.x;
}
ull yRect(int numPoints, point *points)
{
    sort(&points[0], &points[numPoints], cmpY); //y then x
    //add the x's to set
    multiset<int> xs;
    for (int i = 0; i < numPoints; i++)
        xs.insert(points[i].x);
    //loop through by y (cuts points in half) -> enclose both halves
    int minX = points[0].x, maxX = points[0].x;
    ull minArea = BIG_NUM, arr1, arr2;
    for (int i = 0; i < numPoints - 1; i++)
    {
        //handle x ...
        xs.erase(xs.find(points[i].x));
        if (points[i].x < minX)
            minX = points[i].x;
        else if (points[i].x > maxX)
            maxX = points[i].x;
        if (points[i].y == points[i + 1].y)
            continue;
        //find 2 halves areas and change minArea
        arr1 = (ull)(points[i].y - points[0].y) * (ull)(maxX - minX);
        arr2 = (ull)(points[numPoints - 1].y - points[i + 1].y) *
               (ull)((*xs.rbegin()) - (*xs.begin()));
        minArea = min(minArea, arr1 + arr2);
    }
    return minArea;
}
int main(void)
{
    //read
    FILE *junk;
    junk = freopen("split.in", "r", stdin);
    junk = freopen("split.out", "w", stdout);
    int numPoints;
    cin >> numPoints;
    point *points = new point[numPoints];
    for (int i = 0; i < numPoints; i++)
        cin >> points[i].x >> points[i].y;

    //get rects
    ull total_sz = bigRect(numPoints, points); //find rect size
    ull x_sz = xRect(numPoints, points);       //x order
    ull y_sz = yRect(numPoints, points);       //y order

    //print
    cout << total_sz - min(min(x_sz, y_sz), total_sz);
    return 0;
}