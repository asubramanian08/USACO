// Start: 8:50
// Think: 9:02
// Write: 9:18
// Debug: 9:48 -> 9/10 timeout/callstack
// After looking at sol: 12:02 - 12:15 (quick fix)
#include <iostream>
#include <set>
using namespace std;

typedef pair<int, int> point;
#define x first
#define y second
#define BIG_NUM 10000000
set<point> bales, vis;
int lowX, lowY, highX, highY, perimeter = 0;

bool is_relevent(point pt)
{
    for (int i = -1; i <= 1; i++)
        for (int j = -1; j <= 1; j++)
            if (bales.find(pair(pt.x + i, pt.y + j)) != bales.end())
                return true;
    return false;
}
void floodfill(point pos)
{
    //current node
    if (bales.find(pos) != bales.end())
    {
        perimeter++;
        return;
    }
    if (vis.find(pos) != vis.end())
        return;
    vis.insert(pos);
    //added is relevent -> simple optimization after sol
    if (!is_relevent(pos))
        return;

    //other nodes
    if (pos.x > lowX)
        floodfill(pair(pos.x - 1, pos.y));
    if (pos.y > lowY)
        floodfill(pair(pos.x, pos.y - 1));
    if (pos.x < highX)
        floodfill(pair(pos.x + 1, pos.y));
    if (pos.y < highY)
        floodfill(pair(pos.x, pos.y + 1));
}

int main(void)
{
    //read
#ifndef HOME
    freopen("perimeter.in", "r", stdin);
    freopen("perimeter.out", "w", stdout);
#endif
    int numBayles;
    cin >> numBayles;
    point pt;
    lowX = lowY = BIG_NUM;
    highX = highY = 0;
    for (int i = 0; i < numBayles; i++)
    {
        cin >> pt.x >> pt.y;
        bales.insert(pt);
        lowX = min(lowX, pt.x);
        lowY = min(lowY, pt.y);
        highX = max(highX, pt.x);
        highY = max(highY, pt.y);
    }
    lowX--;
    lowY--;
    highX++;
    highY++;

    //run and print
    floodfill(pair(bales.begin()->x - 1, bales.begin()->y)); //this also changed after sol fix
    cout << perimeter << endl;
    return 0;
}