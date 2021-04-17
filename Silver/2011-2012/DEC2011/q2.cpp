// Start: 9:35
// Think: 9:40
// Write: 10:59
// Debug: 11:55 - 11:58 -> manual testing
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

typedef pair<int, int> path;
#define mp make_pair
class conn
{
public:
    int wt, pos, from;
    conn() {}
    conn(int x, int y, int z)
    {
        wt = x;
        pos = y;
        from = z;
    }
    bool operator<(const conn &m) const
    {
        return wt > m.wt;
    }
    void operator=(const conn &m)
    {
        wt = m.wt;
        pos = m.pos;
        from = m.from;
    }
};

vector<conn> *fields;
int numFields, numPaths;
int *ptFrom;

int shortestPath(void)
{
    for (int i = 0; i < numFields; i++)
        ptFrom[i] = -1;
    priority_queue<conn> pq;
    pq.push(conn(0, 0, 0));
    conn currPath = pq.top();
    while (currPath.pos != numFields - 1)
    {
        //handle this
        pq.pop();
        ptFrom[currPath.pos] = currPath.from;

        //do others
        for (int i = 0; i < fields[currPath.pos].size(); i++)
            if (ptFrom[fields[currPath.pos][i].pos] == -1)
                pq.push(conn(currPath.wt + fields[currPath.pos][i].wt,
                             fields[currPath.pos][i].pos, currPath.pos));

        currPath = pq.top();
    }
    ptFrom[currPath.pos] = currPath.from;
    return currPath.wt;
}

int main(void)
{
    //read
#ifndef HOME
    freopen("rblock.in", "r", stdin);
    freopen("rblock.out", "w", stdout);
#endif
    cin >> numFields >> numPaths;
    fields = new vector<conn>[numFields];
    int f1, f2, wt;
    for (int i = 0; i < numPaths; i++)
    {
        cin >> f1 >> f2 >> wt;
        f1--;
        f2--;
        fields[f1].push_back(conn(wt, f2, fields[f2].size()));
        fields[f2].push_back(conn(wt, f1, fields[f1].size() - 1));
    }

    //find the original path
    ptFrom = new int[numFields];
    int orgDist = shortestPath();
    int *orgFrom = new int[numFields];
    memcpy(orgFrom, ptFrom, sizeof(int) * numFields);

    //block off paths
    int maxDist = orgDist;
    for (int i = 0; i < numFields; i++)
        for (int j = 0; j < fields[i].size(); j++)
            if (fields[i][j].pos == orgFrom[i])
            {
                fields[i][j].wt *= 2;
                fields[fields[i][j].pos][fields[i][j].from].wt *= 2;
                maxDist = max(maxDist, shortestPath());
                fields[i][j].wt /= 2;
                fields[fields[i][j].pos][fields[i][j].from].wt /= 2;
            }

    //print and delete
    cout << (maxDist - orgDist);
    delete[] fields;
    delete[] ptFrom;
    delete[] orgFrom;
    return 0;
}