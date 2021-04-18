// Start: 10:29
// Think: 10:30
// Write: 11:09
// Debug: 11:38
//made after q1.txt
#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <queue>
using namespace std;

typedef pair<int, int> point;
#define x first
#define y second
#define mp make_pair

int numFarms;
point *farms;
vector<int> xComp, yComp;

void xCompress()
{
    //get impPoints
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

    //form xComp and map
    int dist = 0;
    map<int, int> newVal;
    for (int i = 1; i < impPoints.size(); i++)
    {
        xComp.push_back(impPoints[i] - impPoints[i - 1]);
        dist += xComp[i - 1];
        newVal[dist] = xComp.size();
    }
    xComp.push_back(1);

    //change values
    for (int i = 0; i < numFarms; i++)
        farms[i].x = newVal[farms[i].x];
}
void yCompress()
{
    //get impPoints
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

    //form yComp and map
    int dist = 0;
    map<int, int> newVal;
    for (int i = 1; i < impPoints.size(); i++)
    {
        yComp.push_back(impPoints[i] - impPoints[i - 1]);
        dist += yComp[i - 1];
        newVal[dist] = yComp.size();
    }
    yComp.push_back(1);

    //fix values
    for (int i = 0; i < numFarms; i++)
        farms[i].y = newVal[farms[i].y];
}

point *sortFarms;
bool **vis;
typedef pair<point, int> inst;
int BFS(int start, int end)
{
    queue<inst> BFSq;
    BFSq.push(mp(farms[start], 0));
    inst currPos;
    while (BFSq.size() != 0)
    {
        //handle this one
        currPos = BFSq.front();
        BFSq.pop();
        if (currPos.first == farms[end])
            return currPos.second;
        if (vis[currPos.first.x][currPos.first.y])
            continue;
        vis[currPos.first.x][currPos.first.y] = true;
        int inFarms = lower_bound(&sortFarms[0], &sortFarms[numFarms], currPos.first) - &sortFarms[0];
        if ((sortFarms[inFarms] == currPos.first) && (sortFarms[inFarms] != farms[start]))
            continue;

        //go to others
        if (currPos.first.x > 0)
            BFSq.push(mp(mp(currPos.first.x - 1, currPos.first.y), currPos.second + xComp[currPos.first.x - 1]));
        if (currPos.first.y > 0)
            BFSq.push(mp(mp(currPos.first.x, currPos.first.y - 1), currPos.second + yComp[currPos.first.y - 1]));
        if (currPos.first.x < xComp.size() - 1)
            BFSq.push(mp(mp(currPos.first.x + 1, currPos.first.y), currPos.second + xComp[currPos.first.x + 1]));
        if (currPos.first.y < yComp.size() - 1)
            BFSq.push(mp(mp(currPos.first.x, currPos.first.y + 1), currPos.second + yComp[currPos.first.y + 1]));
    }
    return -1;
}

int main(void)
{
    //read
#ifndef HOME
    freopen("delivery.in", "r", stdin);
    freopen("delivery.out", "w", stdout);
#endif
    cin >> numFarms;
    farms = new point[numFarms];
    for (int i = 0; i < numFarms; i++)
        cin >> farms[i].x >> farms[i].y;

    //set up - compress the points ...
    xCompress();
    yCompress();
    sortFarms = new point[numFarms];
    copy(&farms[0], &farms[numFarms], &sortFarms[0]);
    sort(&sortFarms[0], &sortFarms[numFarms]);
    vis = new bool *[xComp.size()];
    for (int i = 0; i < xComp.size(); i++)
        vis[i] = new bool[yComp.size()];

    //BFS the grid
    int total = 0, curr;
    for (int i = 0; i < numFarms; i++)
    {
        for (int i = 0; i < xComp.size(); i++)
            fill(&vis[i][0], &vis[i][yComp.size()], false);
        curr = BFS(i, (i + 1) % numFarms);
        if (curr == -1)
        {
            cout << "-1";
            return 0;
        }
        total += curr;
    }

    //delete add print
    cout << total;
    delete[] farms;
    delete[] sortFarms;
    for (int i = 0; i < xComp.size(); i++)
        delete[] vis[i];
    delete[] vis;
    return 0;
}