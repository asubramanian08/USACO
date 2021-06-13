/*USACO MAR13 Problem 'painting' Analysis by Jakub Pachocki

Since the fences do not intersect, an enclosure is contained in another enclosure if and only if its 
upper right corner is.

We can solve the problem using a plane sweep. We will maintain a set S of rectangles that are not enclosed 
in any other in the sweep. A point P is inside some enclosure if a vertical line drawn upwards from P hits 
a top edge of an enclosure in S before it hits some bottom edge. We treat each horizontal edge as two 
events: one when we first encounter it, and one when the sweep line moves off its right end point. Then we 
can process all these events along with vertices in a left- to-right order, and maintain the positions of 
the horizontal edges of the currently relevant enclosures and using a balanced tree (STL set). A ray 
shooting then becomes checking for a successor of the vertex's y- coordinate, which can be done using the 
lower_bound operation in set.

The following is a sample solution:*/
#include <cstdio>
#include <algorithm>
#include <set>
using namespace std;
#define N 50005
#define INF 100000000
typedef pair<int, pair<int, int>> pp;
int n, rect[N][4], c;
pp edges[2 * N];
bool seen[N];
FILE *in = fopen("painting.in", "r"), *out = fopen("painting.out", "w");
multiset<pair<int, int>> s;
int main()
{
    fscanf(in, "%d", &n);
    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            fscanf(in, "%d", &rect[i][j]);
        }
        edges[2 * i] = make_pair(rect[i][0], make_pair(i, 1));
        edges[2 * i + 1] = make_pair(rect[i][2], make_pair(i, 0));
    }
    sort(edges, edges + 2 * n);
    s.insert(make_pair(INF, 1));
    for (int i = 0; i < 2 * n; ++i)
    {
        int index = edges[i].second.first;
        int start = edges[i].second.second;
        pair<int, int> p = *(s.lower_bound(make_pair(rect[index][1], -1)));
        if (start)
        {
            if (p.second == 1)
            {
                ++c;
                seen[index] = 1;
                s.insert(make_pair(rect[index][1], 1));
                s.insert(make_pair(rect[index][3], 0));
            }
        }
        else
        {
            if (seen[index])
            {
                s.erase(s.find(make_pair(rect[index][1], 1)));
                s.erase(s.find(make_pair(rect[index][3], 0)));
            }
        }
    }
    fprintf(out, "%d\n", c);
    return 0;
}