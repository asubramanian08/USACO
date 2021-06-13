#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <map>
#include <cstring>
using namespace std;

typedef pair<int, int> point;
#define x first
#define y second
#define mp make_pair
#define BIG_NUM 10000000

vector<int> xComp, yComp;
int numFarms, farmTo, farmFrom;
point *farms;
bool **vis;
point *newFarms;

void xCompress()
{
    //find the impPoints
    vector<int> impPoints;
    for (int i = 0; i < numFarms; i++)
    {
        impPoints.push_back(farms[i].x);
        impPoints.push_back(farms[i].x + 1);
        impPoints.push_back(farms[i].x - 1);
    }
    impPoints.push_back(0);
    sort(impPoints.begin(), impPoints.end());
    impPoints.resize(unique(impPoints.begin(), impPoints.end()) - impPoints.begin());

    //make the xComp
    for (int i = 1; i < impPoints.size(); i++)
        xComp.push_back(impPoints[i] - impPoints[i - 1]);
    xComp.push_back(1); //after everything

    //make map
    int dist = 0;
    map<int, int> valChange;
    for (int i = 0; i < xComp.size(); i++)
    {
        valChange[dist] = i;
        dist += xComp[i];
    }

    //fix values
    for (int i = 0; i < numFarms; i++)
        farms[i].x = valChange[farms[i].x];
}
void yCompress()
{
    //find the impPoints
    vector<int> impPoints;
    for (int i = 0; i < numFarms; i++)
    {
        impPoints.push_back(farms[i].y);
        impPoints.push_back(farms[i].y + 1);
        impPoints.push_back(farms[i].y - 1);
    }
    impPoints.push_back(0);
    sort(impPoints.begin(), impPoints.end());
    impPoints.resize(unique(impPoints.begin(), impPoints.end()) - impPoints.begin());

    //make the yComp
    for (int i = 1; i < impPoints.size(); i++)
        yComp.push_back(impPoints[i] - impPoints[i - 1]);
    yComp.push_back(1); //after everything

    //make map
    int dist = 0;
    map<int, int> valChange;
    for (int i = 0; i < yComp.size(); i++)
    {
        valChange[dist] = i;
        dist += yComp[i];
    }

    //fix values
    for (int i = 0; i < numFarms; i++)
        farms[i].y = valChange[farms[i].y];
}

int BFS(void)
{
    point currPlace = farms[farmFrom];
    queue<pair<point, int>> BFSq;
    BFSq.push(mp(currPlace, 0));
    int depth, idx;
    while (BFSq.size() != 0)
    {
        //queue handeling
        currPlace = BFSq.front().first;
        depth = BFSq.front().second;
        BFSq.pop();

        //got there
        if (currPlace == farms[farmTo])
            return depth;
        //been here before
        if (vis[currPlace.x][currPlace.y])
            continue;
        vis[currPlace.x][currPlace.y] = true;
        //in a farm
        idx = lower_bound(&newFarms[0], &newFarms[numFarms], currPlace) - &newFarms[0];
        if ((newFarms[idx] == currPlace) && (newFarms[idx] != farms[farmFrom]))
            continue;

        //going to places
        if (currPlace.x > 0)
            BFSq.push(mp(mp(currPlace.x - 1, currPlace.y), depth + xComp[currPlace.x - 1]));
        if (currPlace.x < xComp.size() - 1)
            BFSq.push(mp(mp(currPlace.x + 1, currPlace.y), depth + xComp[currPlace.x + 1]));
        if (currPlace.y > 0)
            BFSq.push(mp(mp(currPlace.x, currPlace.y - 1), depth + yComp[currPlace.y - 1]));
        if (currPlace.y < yComp.size() - 1)
            BFSq.push(mp(mp(currPlace.x, currPlace.y + 1), depth + yComp[currPlace.y + 1]));
    }
    return BIG_NUM;
}

int main(void)
{
    //read
    FILE *junk;
    junk = freopen("delivery.in", "r", stdin);
    junk = freopen("delivery.out", "w", stdout);
    cin >> numFarms;
    farms = new point[numFarms];
    for (int i = 0; i < numFarms; i++)
        cin >> farms[i].x >> farms[i].y;

    //coordinate compression
    xCompress();
    yCompress();

    //BFS
    newFarms = new point[numFarms];
    memcpy(newFarms, farms, sizeof(point) * numFarms);
    sort(&newFarms[0], &newFarms[numFarms]);
    int totalDist = 0, currDist;
    vis = new bool *[xComp.size()];
    for (int i = 0; i < xComp.size(); i++)
        vis[i] = new bool[yComp.size()];

    //BFS
    for (int i = 0; i < numFarms; i++)
    {
        for (int i = 0; i < xComp.size(); i++)
            memset(vis[i], 0, sizeof(bool) * yComp.size());
        farmTo = (i + 1) % numFarms;
        farmFrom = i;
        currDist = BFS();
        if (currDist == BIG_NUM)
        {
            std::cout << "-1";
            return 0;
        }
        totalDist += currDist;
    }

    //delete and print
    delete[] farms;
    std::cout << totalDist;
    return 0;
}