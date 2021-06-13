#include <iostream>
#include <algorithm>
#include <cmath>
#include <stack>
#include <vector>
using namespace std;

typedef pair<int, int> point;
#define x first
#define y second
#define mp make_pair
typedef long long ll;

//convexHull + funcs
point p0;
ll sqr_dist(point &p1, point &p2)
{
    return (ll)(p1.x - p2.x) * (ll)(p1.x - p2.x) +
           (ll)(p1.y - p2.y) * (ll)(p1.y - p2.y);
}
void swapPt(point &p1, point &p2)
{
    point temp = p1;
    p1 = p2;
    p2 = temp;
}
int orient(point &p1, point &p2, point &p3)
{
    ll val = (ll)(p2.y - p1.y) * (ll)(p3.x - p2.x) -
             (ll)(p2.x - p1.x) * (ll)(p3.y - p2.y);

    if (val == 0)
        return 0;
    return (val > 0) ? -1 : 1;
}
bool cmpAng(point &p1, point &p2)
{
    int o = orient(p0, p1, p2);
    if (o == 0)
        return sqr_dist(p0, p1) < sqr_dist(p0, p2);
    return o > 0;
}
vector<point> convexHull(int numPoints, point *points)
{
    //sort array (by the angle from the smallest yPoint)
    int minPt = 0;
    for (int i = 0; i < numPoints; i++)
        if (points[i].y < points[minPt].y ||
            (points[i].y == points[minPt].y &&
             points[i].x < points[minPt].x))
            minPt = i;
    swapPt(points[0], points[minPt]);
    p0 = points[0];
    sort(&points[1], &points[numPoints], cmpAng);

    //find the hull (stack)
    stack<int> hull;
    hull.push(0);
    hull.push(1);
    int p1, p2, p3; //from closest to start
    for (int i = 2; i < numPoints; i++)
    {
        do
        {
            //find the 3 points
            p3 = i;
            p2 = hull.top();
            hull.pop();
            p1 = hull.top();
            //check
        } while ((hull.size() > 1) && (orient(points[p1], points[p2], points[p3]) <= 0));
        hull.push(p2);
        hull.push(p3);
    }

    //return (vector from stack)
    vector<point> hullVtr;
    while (hull.size() != 0)
    {
        hullVtr.push_back(points[hull.top()]);
        hull.pop();
    }
    reverse(hullVtr.begin(), hullVtr.end());
    return hullVtr;
}

void divideHull(vector<point> &&hull, vector<point> &low, vector<point> &high)
{
    //find left and right most
    int leftMost = 0, rightMost = 0;
    for (int i = 1; i < hull.size(); i++)
        if (hull[i] < hull[leftMost])
            leftMost = i;
        else if (hull[i] > hull[rightMost])
            rightMost = i;

    int nextPos, startPos;
    //get low hull
    low.push_back(hull[leftMost]);
    for (int i = leftMost; i != rightMost; i = nextPos)
    {
        nextPos = i + 1;
        if (nextPos == hull.size())
            nextPos = 0;
        low.push_back(hull[nextPos]);
    }
    //get high hull
    high.push_back(hull[rightMost]);
    for (int i = rightMost; i != leftMost; i = nextPos)
    {
        nextPos = i + 1;
        if (nextPos == hull.size())
            nextPos = 0;
        high.push_back(hull[nextPos]);
    }
    reverse(high.begin(), high.end());
}

//point in a convex polygons
int lineSide(point &l1, point &l2, point &pt)
{
    if (orient(l1, l2, pt) == 0)
    {
        if (pt.y > max(l1.y, l2.y))
            return 1;
        if (pt.y < min(l1.y, l2.y))
            return -1;
        return 0; //on line
    }
    //side true - up, false- down
    point upPt = mp(l1.x, l1.y + 1);
    bool side = orient(l1, l2, pt) == orient(l1, l2, upPt);
    return side ? 1 : -1;
}
bool inside(vector<point> &high, vector<point> &low, point &pt)
{
    //goes from left to right - down curve
    int pos;
    //check higher side
    pos = lower_bound(high.begin(), high.end(), pt) - high.begin();
    if ((pos == 0) && (high[0].x == high[1].x))
        pos = 1;
    if (pos == 0 || pos == high.size())
        return false;
    if (lineSide(high[pos - 1], high[pos], pt) > 0)
        return false; //higher then line

    //check lower side
    pos = lower_bound(low.begin(), low.end(), pt) - low.begin();
    if ((pos == 0) && (low[0].x == low[1].x))
        pos = 1;
    if (pos == 0 || pos == low.size())
        return false;
    if (lineSide(low[pos - 1], low[pos], pt) < 0)
        return false; //lower then line
    return true;
}

int main(void)
{
    //read
    FILE *junk;
    junk = freopen("curling.in", "r", stdin);
    junk = freopen("curling.out", "w", stdout);
    int numStones;
    cin >> numStones;
    point *stones1 = new point[numStones];
    for (int i = 0; i < numStones; i++)
        cin >> stones1[i].x >> stones1[i].y;
    point *stones2 = new point[numStones];
    for (int i = 0; i < numStones; i++)
        cin >> stones2[i].x >> stones2[i].y;

    //find the hulls and right left points
    vector<point> low1, high1, low2, high2;
    divideHull(convexHull(numStones, stones1), low1, high1);
    divideHull(convexHull(numStones, stones2), low2, high2);

    //points in hull + print
    int a;
    for (int i = 0; i < numStones; i++)
        if (inside(high1, low1, stones1[i]) != true)
            a = 0;
    int score1 = 0, score2 = 0;
    for (int i = 0; i < numStones; i++)
    {
        score1 += inside(high1, low1, stones2[i]);
        score2 += inside(high2, low2, stones1[i]);
    }
    cout << score1 << ' ' << score2;
    return 0;
}