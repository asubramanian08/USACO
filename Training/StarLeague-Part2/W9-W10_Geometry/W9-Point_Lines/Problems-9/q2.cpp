//Min dist between points -> brute force with sorting || FASTER algo. in slides
#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;

typedef pair<int, int> point;
#define BIG_NUM 10000000000000

int main(void)
{
    //read
    /*FILE *junk;
    junk = freopen("mindist.in", "r", stdin);
    junk = freopen("mindist.out", "w", stdout);*/
    int numPoints;
    cin >> numPoints;
    point *points = new point[numPoints];
    for (int i = 0; i < numPoints; i++)
        cin >> points[i].first >> points[i].second;

    //sort (by x)
    sort(&points[0], &points[numPoints]);

    //compute ans and print
    long long minDist = BIG_NUM, currDist;
    for (int i = 0; i < numPoints; i++)
        for (int j = i + 1; (j < numPoints) && (points[j].first - points[i].first <= minDist); j++)
        {
            currDist = pow(points[i].first - points[j].first, 2) +
                       pow(points[i].second - points[j].second, 2);
            if (currDist < minDist)
                minDist = currDist;
        }
    cout << minDist;
    return 0;
}