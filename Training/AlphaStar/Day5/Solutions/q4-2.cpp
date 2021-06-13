/* An alternative approach is to do a recursive "flood fill" of the grid containing our object, starting 
from a cell that is definitely outside the object such as (0,0). That is, whenever we visit a cell, we 
mark it as having been visited (to avoid cycling) and then recursively visit its 4 neighbors, as long as 
these neighbors are empty cells. If we check a neighboring cell that is occupied with part of the object, 
we increment our perimeter count instead of visiting that cell recursively. We must be slightly careful, 
however, not to waste time filling the _entire_ grid, since this will take too long. Instead, we start our 
flood fill from a square we know is next to the object (e.g., one cell directly west of the west-most cell 
on the object), and if we ever notice that we have wandered off to a cell surrounded by empty space in all 
8 directions, we return from our recursive function immediately. This keeps our search localized around 
the boundary, and our running time linear.

Here is Brian Dean's recursive solution written in C++: */

#include <iostream>
#include <cstdio>
#include <set>
using namespace std;
typedef pair<int, int> Point;
set<Point> object, visited;
int perimeter;
bool isolated(int x, int y)
{
    for (int i = -1; i <= 1; i++)
        for (int j = -1; j <= 1; j++)
            if (object.count(Point(x + i, y + j)))
                return false;
    return true;
}
void visit(int x, int y)
{
    if (object.count(Point(x, y)))
    {
        perimeter++;
        return;
    }
    if (visited.count(Point(x, y)))
        return;
    visited.insert(Point(x, y));
    if (isolated(x, y))
        return;
    visit(x - 1, y);
    visit(x + 1, y);
    visit(x, y - 1);
    visit(x, y + 1);
}
int main(void)
{
    int N, x, y;
    freopen("perimeter.in", "r", stdin);
    freopen("perimeter.out", "w", stdout);
    cin >> N;
    for (int i = 0; i < N; i++)
    {
        cin >> x >> y;
        object.insert(Point(x, y));
    }
    Point start = *object.begin();
    x = start.first - 1;
    y = start.second;
    visit(x, y);
    cout << perimeter << "\n";
    return 0;
}