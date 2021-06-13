#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
using namespace std;

//defineing types
typedef pair<int, int> point;
#define x first
#define y second
typedef pair<point, point> fence;
typedef vector<fence> poly;
typedef pair<int, int> pii;
#define mp make_pair

//initializing all vars
#define NA -1
int numFences, numCows;
fence *fences;
point *cows;
vector<poly> polys;
int *poly_dpt;
int *poly_sz;

//setup funcs
void read()
{
    FILE *junk;
    junk = freopen("crazy.in", "r", stdin);
    junk = freopen("crazy.out", "w", stdout);
    cin >> numFences >> numCows;
    //put in fence points
    fences = new fence[numFences];
    for (int i = 0; i < numFences; i++)
        cin >> fences[i].first.x >> fences[i].first.y >>
            fences[i].second.x >> fences[i].second.y;
    //add the cows
    cows = new point[numCows];
    for (int i = 0; i < numCows; i++)
        cin >> cows[i].x >> cows[i].y;
}
bool cmp(int &fp1, int &fp2)
{
    //set points
    point p1, p2;
    if (fp1 & 1)
        p1 = fences[fp1 / 2].second;
    else
        p1 = fences[fp1 / 2].first;
    if (fp2 & 1)
        p2 = fences[fp2 / 2].second;
    else
        p2 = fences[fp2 / 2].first;

    //returning
    if (p1 != p2)
        return p1 < p2;
    return fp1 < fp2;
}
pii *findFences()
{
    int *fencePoints = new int[numFences * 2];
    for (int i = 0; i < numFences * 2; i++)
        fencePoints[i] = i;
    sort(&fencePoints[0], &fencePoints[numFences * 2], cmp);
    pii *fenceConns = new pii[numFences];
    for (int i = 0; i < numFences; i++)
    {
        if (fencePoints[i * 2] & 1)
            fenceConns[fencePoints[i * 2] / 2].second = fencePoints[i * 2 + 1];
        else
            fenceConns[fencePoints[i * 2] / 2].first = fencePoints[i * 2 + 1];
        if (fencePoints[i * 2 + 1] & 1)
            fenceConns[fencePoints[i * 2 + 1] / 2].second = fencePoints[i * 2];
        else
            fenceConns[fencePoints[i * 2 + 1] / 2].first = fencePoints[i * 2];
    }
    delete[] fencePoints;
    return fenceConns;
}
void nextFence(int point, bool *vis, pii *fenceConns, int currPoly)
{
    if (vis[point / 2])
        return;
    polys[currPoly].push_back(fences[point / 2]);
    vis[point / 2] = true;
    if (point & 1)
        nextFence(fenceConns[point / 2].first, vis, fenceConns, currPoly);
    else
        nextFence(fenceConns[point / 2].second, vis, fenceConns, currPoly);
}

//finding polygon functions
typedef long long ll;
int orient(point &p1, point &p2, point &p3)
{
    ll val = (ll)(p2.y - p1.y) * (ll)(p3.x - p2.x) -
             (ll)(p2.x - p1.x) * (ll)(p3.y - p2.y);

    if (val == 0)
        return 0;
    return (val > 0) ? -1 : 1;
}
int side(point &pt, fence &ln)
{
    if (orient(ln.first, ln.second, pt) == 0)
        return 0; //on line
    //side true - up, false- down
    point upPt = mp(ln.first.x, ln.first.y + 1);
    bool side = orient(ln.first, ln.second, pt) == orient(ln.first, ln.second, upPt);
    return side ? 1 : -1;
}
bool between(int r1, int r2, int p)
{
    if ((min(r1, r2) < p) && (p <= max(r1, r2)))
        return true;
    return false;
}
bool inside(poly &p, point &pt)
{
    int timesCross = 0;
    for (int i = 0; i < p.size(); i++)
        timesCross += (side(pt, p[i]) >= 0) && between(p[i].first.x, p[i].second.x, pt.x);
    return timesCross & 1;
}
void set_poly(int p)
{
    if (poly_sz[p] != NA)
        return;
    int insideCows = 0;
    //subtract the inside polygons
    for (int i = 0; i < polys.size(); i++)
    {
        if (i == p || !inside(polys[p], polys[i][0].first))
            continue;
        set_poly(i);
        insideCows -= poly_sz[i];
    }
    //add all cows that are inside
    for (int i = 0; i < numCows; i++)
        insideCows += inside(polys[p], cows[i]);
    poly_sz[p] = insideCows;
}

int main(void)
{
    //setup -> get the cows and polygons
    read();
    pii *fenceConns = findFences();
    bool *vis_fence = new bool[numFences];
    memset(vis_fence, false, sizeof(bool) * numFences);
    for (int i = 0; i < numFences; i++)
        if (!vis_fence[i])
        {
            polys.push_back(poly());
            nextFence(i * 2, vis_fence, fenceConns, polys.size() - 1);
        }
    delete[] fenceConns;
    delete[] vis_fence;

    //find biggest -> loop through the polygons
    int maxPop = 0;
    poly_sz = new int[polys.size()];
    for (int i = 0; i < polys.size(); i++)
        poly_sz[i] = NA;
    for (int i = 0; i < polys.size(); i++)
    {
        set_poly(i);
        maxPop = max(maxPop, poly_sz[i]);
    }
    int outside = numCows;
    for (int i = 0; i < polys.size(); i++)
        outside -= poly_sz[i];
    maxPop = max(maxPop, outside);

    //print & delete & return
    delete[] poly_sz;
    delete[] cows;
    cout << maxPop;
    return 0;
}