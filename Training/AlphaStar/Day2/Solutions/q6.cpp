/*USACO JAN13 Problem 'paint' Analysis by Jonathan Paulson

If we knew the area Bessie was going to paint were small, this would be easy; we could just explicitly 
keep track of how many coats of paint each unit of fence had. Unfortunately, we don't.

But...Bessie only stops on at most 100,001 different points (one per move). So these are the only 
"interesting coordinates". In particular, any two points between two "interesting coordinates" will have 
the same number of coats of paint (this idea is a generally useful trick called "coordinate compression", 
and it's worth knowing). So it's enough to keep track of the number of coats of paint along each of these 
100,002 segments.

This still might not be fast enough; each move could cover all 100,002 segments, so this algorithm still 
looks quadratic. So we can apply another useful trick, which is just keeping track of the deltas 
introduced by each of Bessie's moves. Each of Bessie's moves is a segment (on our coordinate-compressed 
line), and at the beginning of the segment we write down "+1 coats of paint" and at the end of the segment
we write down "-1 coats of paint". Then if we scan from left to right, we can add up the deltas as we go, 
and keep track of the number of coats on each segment.

This gives an O(n lg n) solution (to "scan from left to right", we need to sort the segments). It was a 
bit of a winding logical path to get here, so the final solution may not be quite clear. Take a look at 
Travis Hance's solution, which presents the idea quite elegantly: (and remember coordinate compression and
deltas-for-segments for later!)*/

#include <cstdio>
#include <algorithm>
using namespace std;
#define NMAX 100005
struct Event
{
    int x;
    int inc;
    bool operator<(Event const &e) const
    {
        return x < e.x;
    }
};
Event events[2 * NMAX];
int main()
{
    freopen("paint.in", "r", stdin);
    freopen("paint.out", "w", stdout);
    int n, k;
    scanf("%d", &n);
    scanf("%d", &k);
    int x = 0;
    for (int i = 0; i < n; i++)
    {
        int dist;
        scanf("%d", &dist);
        char c;
        do
        {
            c = fgetc(stdin);
        } while (c != 'L' && c != 'R');
        int x1 = x + dist * (c == 'L' ? -1 : 1);
        events[2 * i].x = min(x, x1);
        events[2 * i].inc = 1;
        events[2 * i + 1].x = max(x, x1);
        events[2 * i + 1].inc = -1;
        x = x1;
    }
    sort(events, events + (2 * n));
    int nCoats = 0;
    int answer = 0;
    for (int i = 0; i < 2 * n; i++)
    {
        if (i > 0 && nCoats >= k)
        {
            answer += events[i].x - events[i - 1].x;
        }
        nCoats += events[i].inc;
    }
    printf("%d\n", answer);
}