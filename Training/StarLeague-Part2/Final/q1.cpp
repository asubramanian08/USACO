#include <iostream>
#include <algorithm>
#include <set>
using namespace std;

struct rect
{
    int xStart, xEnd, yStart, yEnd;
};
struct eventPoint
{
    int x, rectNum;
    bool is_start;
};
typedef pair<int, int> pii;
#define mp make_pair

bool cmp(eventPoint &ep1, eventPoint &ep2)
{
    return ep1.x < ep2.x;
}

int main(void)
{
    //read
    FILE *junk;
    junk = freopen("planting.in", "r", stdin);
    junk = freopen("planting.out", "w", stdout);
    int numRects;
    cin >> numRects;
    rect *rects = new rect[numRects];
    for (int i = 0; i < numRects; i++)
        cin >> rects[i].xStart >> rects[i].yEnd >>
            rects[i].xEnd >> rects[i].yStart;

    //make eventPoints
    eventPoint *eventPoints = new eventPoint[numRects * 2];
    for (int i = 0; i < numRects; i++)
    {
        eventPoints[i * 2].x = rects[i].xStart;
        eventPoints[i * 2].is_start = true;
        eventPoints[i * 2].rectNum = i;

        eventPoints[i * 2 + 1].x = rects[i].xEnd;
        eventPoints[i * 2 + 1].is_start = false;
        eventPoints[i * 2 + 1].rectNum = i;
    }
    sort(&eventPoints[0], &eventPoints[numRects * 2], cmp);

    //do sweep line
    int lastX = eventPoints[0].x, currRect;
    multiset<pii> inRects;
    long long area = 0, subArea;
    int startLine, endLine;
    for (int i = 0; i < numRects * 2; i++)
    {
        //find additional area
        startLine = endLine = subArea = 0;
        for (auto i = inRects.begin(); i != inRects.end(); i++)
        {
            if ((i != inRects.begin()) && (i->first < endLine))
                endLine = max(endLine, i->second);
            else
            {
                subArea += endLine - startLine;
                startLine = i->first;
                endLine = i->second;
            }
        }
        subArea += endLine - startLine;
        area += (long long)(eventPoints[i].x - lastX) * subArea;

        //do eventPoint action
        currRect = eventPoints[i].rectNum;
        if (eventPoints[i].is_start)
            inRects.insert(mp(rects[currRect].yStart, rects[currRect].yEnd));
        else
            inRects.erase(inRects.find(mp(rects[currRect].yStart, rects[currRect].yEnd)));
        lastX = eventPoints[i].x;
    }

    //delete and print
    delete[] rects;
    delete[] eventPoints;
    cout << area;
    return 0;
}