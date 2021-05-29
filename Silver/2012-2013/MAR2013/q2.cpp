// Start: 8:41
// Think: 8:54, 9:46-9:59
// Write: 10:26
// Debug: 10:35
#include <iostream>
#include <algorithm>
#include <set>
using namespace std;

struct rect
{
    int x1, y1, x2, y2;
};
rect *rects;
typedef pair<int, bool> evp;
typedef pair<int, int> range;
bool cmp(const evp &e1, const evp &e2)
{
    return (!e1.second ? rects[e1.first].x1 : rects[e1.first].x2) <
           (!e2.second ? rects[e2.first].x1 : rects[e2.first].x2);
}

int main(void)
{
    //read
#ifndef HOME
    freopen("painting.in", "r", stdin);
    freopen("painting.out", "w", stdout);
#endif
    int numRects;
    cin >> numRects;
    rects = new rect[numRects];
    for (int i = 0; i < numRects; i++)
        cin >> rects[i].x1 >> rects[i].y1 >> rects[i].x2 >> rects[i].y2;

    //make event point
    evp *events = new evp[numRects * 2];
    for (int i = 0; i < numRects; i++)
    {
        events[i] = evp(i, false);
        events[i + numRects] = evp(i, true);
    }
    sort(events, events + numRects * 2, cmp);

    //sweep line
    set<range> heights;
    int toPaint = 0;
    for (int i = 0; i < numRects * 2; i++)
    {
        rect currRect = rects[events[i].first];
        range currRange(currRect.y2, currRect.y1);
        if (events[i].second) //removing
        {
            heights.erase(currRange);
            continue;
        }
        range has = *heights.lower_bound(currRange);
        if (has.first < currRange.first || has.second > currRange.second)
        {
            toPaint++;
            heights.insert(currRange);
        }
    }

    //print and delete
    cout << toPaint << endl;
    delete[] rects;
    delete[] events;
    return 0;
}