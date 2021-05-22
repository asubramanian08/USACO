// Start: 1:00
// Think: 1:12
// Write: 1:27
// Debug: 2:00
#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <queue>
using namespace std;

int main(void)
{
    //read
#ifndef HOME
    freopen("invite.in", "r", stdin);
    freopen("invite.out", "w", stdout);
#endif
    int numCows, numGroups, groupSize, cow;
    cin >> numCows >> numGroups;
    vector<int> *in_group = new vector<int>[numCows];
    set<int> *groups = new set<int>[numGroups];
    for (int i = 0; i < numGroups; i++)
    {
        cin >> groupSize;
        for (int j = 0; j < groupSize; j++)
        {
            cin >> cow;
            cow--;
            groups[i].insert(cow);
            in_group[cow].push_back(i);
        }
    }

    //BFS and open all the cows
    bool *vis = new bool[numCows];
    fill(vis, vis + numCows, false);
    queue<int> nextCow;
    nextCow.push(0); //every number down one
    int currCow, cowCount;
    vis[0] = true;
    for (cowCount = 0; !nextCow.empty(); cowCount++)
    {
        currCow = nextCow.front();
        nextCow.pop();
        for (int openSet : in_group[currCow])
        {
            groups[openSet].erase(currCow);
            if (groups[openSet].size() == 1)
            {
                int newCow = *(groups[openSet].begin());
                if (!vis[newCow])
                {
                    nextCow.push(newCow);
                    vis[newCow] = true;
                }
            }
        }
    }

    //print
    cout << cowCount << endl;
    return 0;
}