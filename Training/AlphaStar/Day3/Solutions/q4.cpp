/*USACO OPEN12 Problem 'unlock' Analysis

This problem is solved using breadth-first search to find the shortest path from our initial state to a 
state where all objects have disjoint bounding boxes. Our current state is described by 4 numbers, giving 
the (x,y) offset of objects 2 and 3 relative to their initial positions. Each move we make, we can change 
one of these numbers by +1 or -1 to slide either object 2 or 3 (as long as this doesn't create any overlap 
between the objects), or we can change both x offsets or both y offsets by +1 or -1 to simulate moving 
object 1 (since moving object 1 is equivalent to keeping object 1 fixed and moving both objects 2 and 3 in 
the opposite direction).*/

#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <set>
#include <algorithm>
using namespace std;

int n[3];
int lis[3][100][2];
int ok[3][3][51][51];
int dir[4][2] = {-1, 0, 1, 0, 0, 1, 0, -1};
char seen[42][42][42][42];
set<pair<int, int>> occupied;
int check(int i1, int i2, int dx, int dy)
{
    occupied.clear();
    for (int i = 0; i < n[i1]; ++i)
    {
        occupied.insert(make_pair(lis[i1][i][0], lis[i1][i][1]));
    }
    for (int i = 0; i < n[i2]; ++i)
    {
        if (occupied.find(make_pair(lis[i2][i][0] + dx, lis[i2][i][1] + dy)) != occupied.end())
        {
            return 0;
        }
    }
    return 1;
}
int isOkPair(int i1, int i2, int dx, int dy)
{
    if (dx < -20 || dx > 20 || dy < -20 || dy > 20)
        return 1;
    return ok[i1][i2][dx + 20][dy + 20];
}
int isOk(int dx1, int dy1, int dx2, int dy2)
{
    return isOkPair(0, 1, dx1, dy1) && isOkPair(0, 2, dx2, dy2) && isOkPair(1, 2, dx2 - dx1, dy2 - dy1);
}
const int LIM = 20;
char q[3000000][4];
int tail;
void add(int dx1, int dy1, int dx2, int dy2)
{
    if (dx1 < -LIM || dy1 < -LIM || dx1 > LIM || dy1 > LIM ||
        dx2 < -LIM || dy2 < -LIM || dx2 > LIM || dy2 > LIM)
        return;
    if (!isOk(dx1, dy1, dx2, dy2))
        return;
    if (seen[dx1 + LIM][dy1 + LIM][dx2 + LIM][dy2 + LIM])
        return;
    seen[dx1 + LIM][dy1 + LIM][dx2 + LIM][dy2 + LIM] = 1;
    q[tail][0] = dx1;
    q[tail][1] = dy1;
    q[tail][2] = dx2;
    q[tail][3] = dy2;
    tail++;
}
int main()
{
    freopen("unlock.in", "r", stdin);
    freopen("unlock.out", "w", stdout);
    scanf("%d%d%d", &n[0], &n[1], &n[2]);
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < n[i]; ++j)
        {
            scanf("%d%d", &lis[i][j][0], &lis[i][j][1]);
        }
    }
    for (int i1 = 0; i1 < 3; ++i1)
        for (int i2 = 0; i2 < i1; ++i2)
            for (int dx = -20; dx <= 20; ++dx)
                for (int dy = -20; dy <= 20; ++dy)
                {
                    ok[i2][i1][dx + 20][dy + 20] = check(i1, i2, dx, dy);
                }
    memset(seen, 0, sizeof(seen));
    tail = 0;
    add(0, 0, 0, 0);
    for (int i = 0; i < tail; ++i)
    {
        int dx1 = q[i][0];
        int dy1 = q[i][1];
        int dx2 = q[i][2];
        int dy2 = q[i][3];
        if (dx1 == LIM && dy1 == LIM && dx2 == -LIM && dy2 == -LIM)
        {
            puts("1");
            return 0;
        }
        for (int j = 0; j < 4; ++j)
        {
            add(dx1 + dir[j][0], dy1 + dir[j][1], dx2, dy2);
            add(dx1, dy1, dx2 + dir[j][0], dy2 + dir[j][1]);
            add(dx1 + dir[j][0], dy1 + dir[j][1],
                dx2 + dir[j][0], dy2 + dir[j][1]);
        }
    }
}