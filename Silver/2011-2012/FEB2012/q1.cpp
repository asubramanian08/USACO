// Start: 10:24
// Think: 10:27
// Write: 11:08
// Debug: 11:28
// made after q1.txt
#include <iostream>
#include <set>
#include <algorithm>
using namespace std;

typedef pair<int, int> point;
#define x first
#define y second
typedef pair<point, point> rect;
class evtPt
{
public:
    point pt;
    int rect;
    bool is_start;
    bool operator<(const evtPt &ep) const
    {
        return this->pt < ep.pt;
    }
};

rect *rects;
class cmpRect
{
public:
    bool operator()(int x, int y) const
    {
        if (rects[x].first.y == rects[y].first.y)
            return rects[x].first.x > rects[y].first.x;
        return rects[x].first.y > rects[y].first.y;
    }
};

int main(void)
{
    //read
#ifndef HOME
    freopen("planting.in", "r", stdin);
    freopen("planting.out", "w", stdout);
#endif
    int numRects;
    cin >> numRects;
    rects = new rect[numRects];
    for (int i = 0; i < numRects; i++)
        cin >> rects[i].first.x >> rects[i].first.y >>
            rects[i].second.x >> rects[i].second.y;

    //form event points
    evtPt *evtPts = new evtPt[numRects * 2];
    for (int i = 0; i < numRects; i++)
    {
        evtPts[i].pt = rects[i].first;
        evtPts[i].rect = i;
        evtPts[i].is_start = true;
        evtPts[i + numRects].pt = rects[i].second;
        evtPts[i + numRects].rect = i;
        evtPts[i + numRects].is_start = false;
    }
    sort(&evtPts[0], &evtPts[numRects * 2]);

    //do sweep line
    set<int, cmpRect> onRects;
    int lastX = evtPts[0].pt.x, lastY, dist, until;
    long long area = 0;
    for (int i = 0; i < numRects * 2; i++)
    {
        //change area
        dist = 0;
        lastY = rects[*onRects.begin()].first.y;
        until = rects[*onRects.begin()].second.y;
        for (auto onRect : onRects)
            if (until > rects[onRect].first.y)
            {
                dist += lastY - until;
                lastY = rects[onRect].first.y;
                until = rects[onRect].second.y;
            }
            else
                until = min(until, rects[onRect].second.y);
        dist += lastY - until;
        area += dist * (evtPts[i].pt.x - lastX);
        lastX = evtPts[i].pt.x;

        //do the action
        if (evtPts[i].is_start)
            onRects.insert(evtPts[i].rect);
        else
            onRects.erase(evtPts[i].rect);
    }

    //print and delete
    cout << area;
    delete[] rects;
    delete[] evtPts;
    return 0;
}