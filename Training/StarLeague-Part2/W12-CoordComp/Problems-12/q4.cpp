#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
#include <map>
using namespace std;

//types
typedef pair<int, int> point;
#define x first
#define y second
#define mp make_pair
typedef pair<point, point> pasture;

//variable initialize
int width, length, numPastures;
pasture *pastures;
vector<int> xDist, yDist;
bool **vis;

//important functions
void xBlocks()
{
    //find the relevant points
    vector<int> xPts;
    for (int i = 0; i < numPastures; i++)
    {
        xPts.push_back(pastures[i].first.x);
        xPts.push_back(pastures[i].second.x);
    }
    xPts.push_back(1);
    sort(xPts.begin(), xPts.end());
    xPts.resize(unique(xPts.begin(), xPts.end()) - xPts.begin());

    //add the distances
    for (int i = 1; i < xPts.size(); i++)
        xDist.push_back(xPts[i] - xPts[i - 1]);
    if (width + 1 > xPts[xPts.size() - 1])
        xDist.push_back(width - xPts[xPts.size() - 1] + 1);
}
void yBlocks()
{
    //find the relevant points
    vector<int> yPts;
    for (int i = 0; i < numPastures; i++)
    {
        yPts.push_back(pastures[i].first.y);
        yPts.push_back(pastures[i].second.y);
    }
    yPts.push_back(1);
    sort(yPts.begin(), yPts.end());
    yPts.resize(unique(yPts.begin(), yPts.end()) - yPts.begin());

    //add the distances
    for (int i = 1; i < yPts.size(); i++)
        yDist.push_back(yPts[i] - yPts[i - 1]);
    if (length + 1 > yPts[yPts.size() - 1])
        yDist.push_back(length - yPts[yPts.size() - 1] + 1);
}
void xCompress()
{
    //make the map
    map<int, int> compX;
    int total = 1;
    for (int i = 0; i < xDist.size(); i++)
    {
        compX[total] = i;
        total += xDist[i];
    }
    compX[total] = xDist.size();

    //change the coordinates
    for (int i = 0; i < numPastures; i++)
    {
        pastures[i].first.x = compX[pastures[i].first.x];
        pastures[i].second.x = compX[pastures[i].second.x];
    }
}
void yCompress()
{
    //make the map
    map<int, int> compY;
    int total = 1;
    for (int i = 0; i < yDist.size(); i++)
    {
        compY[total] = i;
        total += yDist[i];
    }
    compY[total] = yDist.size();

    //change the coordinates
    for (int i = 0; i < numPastures; i++)
    {
        pastures[i].first.y = compY[pastures[i].first.y];
        pastures[i].second.y = compY[pastures[i].second.y];
    }
}
long long floodFill(point pos)
{
    //current cell
    long long grazed = 0;
    if (vis[pos.x][pos.y])
        return grazed;
    vis[pos.x][pos.y] = true;
    grazed += (long long)xDist[pos.x] * (long long)yDist[pos.y];

    //go to other cells
    if (pos.x > 0)
        grazed += floodFill(mp(pos.x - 1, pos.y));
    if (pos.y > 0)
        grazed += floodFill(mp(pos.x, pos.y - 1));
    if (pos.x < xDist.size() - 1)
        grazed += floodFill(mp(pos.x + 1, pos.y));
    if (pos.y < yDist.size() - 1)
        grazed += floodFill(mp(pos.x, pos.y + 1));
    return grazed;
}

int main(void)
{
    //read
    FILE *junk;
    junk = freopen("grazing.in", "r", stdin);
    junk = freopen("grazing.out", "w", stdout);
    cin >> width >> length >> numPastures;
    pastures = new pasture[numPastures];
    for (int i = 0; i < numPastures; i++)
    {
        cin >> pastures[i].first.x >> pastures[i].first.y >>
            pastures[i].second.x >> pastures[i].second.y;
        pastures[i].second.x++;
        pastures[i].second.y++;
    }

    //compress the coordinates
    xBlocks();
    yBlocks();
    xCompress();
    yCompress();

    //perpare the visited grid -> mark the x's
    vis = new bool *[xDist.size()];
    for (int i = 0; i < xDist.size(); i++)
    {
        vis[i] = new bool[yDist.size()];
        memset(vis[i], 0, sizeof(bool) * yDist.size());
    }
    for (int i = 0; i < numPastures; i++)
        for (int j = pastures[i].first.x; j < pastures[i].second.x; j++)
            for (int k = pastures[i].first.y; k < pastures[i].second.y; k++)
                vis[j][k] = true;

    //flood fill, delete and print
    long long distGrazed = floodFill(mp(0, 0));
    delete[] pastures;
    for (int i = 0; i < xDist.size(); i++)
        delete[] vis[i];
    delete[] vis;
    cout << distGrazed;
    return 0;
}