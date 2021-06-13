#include <iostream>
#include <deque>
#include <vector>
#include <queue>
using namespace std;

typedef pair<int, int> pii;
typedef pair<pii, pii> pii_ii;
//typedef pair<pii, long long> pii_ll;
#define BIG_NUM 100000
#define InRange(x, y) ((x >= 0) && (x < rows) && (y >= 0) && (y < cols))

int main(void)
{
    /*FILE *junk;
    junk = freopen("lilypad.in", "r", stdin);
    junk = freopen("lilypad.out", "w", stdout);*/
    int rows, cols;
    cin >> rows >> cols;
    int **grid = new int *[rows];
    //0: lilly, 1: water, 2: stone
    pii start, end;
    char ch;
    for (int i = 0; i < rows; i++)
    {
        grid[i] = new int[cols];
        for (int j = 0; j < cols; j++)
        {
            cin >> ch;
            ch -= '0';
            if (ch == 0)
                grid[i][j] = 1;
            else if (ch == 2)
                grid[i][j] = 2;
            else
            {
                grid[i][j] = 0;
                if (ch == 3)
                    start = make_pair(i, j);
                else if (ch == 4)
                    end = make_pair(i, j);
            }
        }
    }

    //find 0-1 graph
    vector<pii> **conns = new vector<pii> *[rows];
    for (int i = 0; i < rows; i++)
    {
        conns[i] = new vector<pii>[cols];
        for (int j = 0; j < cols; j++)
        {
            if (InRange(i + 2, j + 1) && (grid[i + 2][j + 1] != 2))
                conns[i][j].push_back(make_pair(i + 2, j + 1));
            if (InRange(i + 2, j - 1) && (grid[i + 2][j - 1] != 2))
                conns[i][j].push_back(make_pair(i + 2, j - 1));
            if (InRange(i - 2, j + 1) && (grid[i - 2][j + 1] != 2))
                conns[i][j].push_back(make_pair(i - 2, j + 1));
            if (InRange(i - 2, j - 1) && (grid[i - 2][j - 1] != 2))
                conns[i][j].push_back(make_pair(i - 2, j - 1));

            if (InRange(i + 1, j + 2) && (grid[i + 1][j + 2] != 2))
                conns[i][j].push_back(make_pair(i + 1, j + 2));
            if (InRange(i - 1, j + 2) && (grid[i - 1][j + 2] != 2))
                conns[i][j].push_back(make_pair(i - 1, j + 2));
            if (InRange(i + 1, j - 2) && (grid[i + 1][j - 2] != 2))
                conns[i][j].push_back(make_pair(i + 1, j - 2));
            if (InRange(i - 1, j - 2) && (grid[i - 1][j - 2] != 2))
                conns[i][j].push_back(make_pair(i - 1, j - 2));
        }
    }

    //init arrays
    int **costGrid = new int *[rows];
    long long **timesGrid = new long long *[rows];
    bool **vis = new bool *[rows];
    for (int i = 0; i < rows; i++)
    {
        costGrid[i] = new int[cols];
        timesGrid[i] = new long long[cols];
        vis[i] = new bool[cols];
        for (int j = 0; j < cols; j++)
        {
            costGrid[i][j] = BIG_NUM;
            timesGrid[i][j] = 0;
            vis[i][j] = false;
        }
    }
    costGrid[start.first][start.second] = 0;
    timesGrid[start.first][start.second] = 1;

    //use deque and figure out path
    /*deque<pii> BFS_DEQ;
    BFS_DEQ.push_front(start);
    pii node;
    while (!BFS_DEQ.empty())
    {
        node = BFS_DEQ.front();
        BFS_DEQ.pop_front();
        for (int i = 0; i < conns[node.first][node.second].size(); i++)
        {
            pii to = conns[node.first][node.second][i];
            if (costGrid[to.first][to.second] > costGrid[node.first][node.second] + grid[to.first][to.second])
            {
                costGrid[to.first][to.second] = costGrid[node.first][node.second] + grid[to.first][to.second];
                if (grid[to.first][to.second] == 0)
                    BFS_DEQ.push_front(to);
                else
                    BFS_DEQ.push_back(to);
            }
        }
    }*/

    /*costGrid[start.first][start.second] = 0;
    timesGrid[start.first][start.second] = 1;
    deque<pii> BFS_DEQ;
    BFS_DEQ.push_front(start);
    pii node;
    while (!BFS_DEQ.empty())
    {
        node = BFS_DEQ.front();
        BFS_DEQ.pop_front();
        for (int i = 0; i < conns[node.first][node.second].size(); i++)
        {
            pii to = conns[node.first][node.second][i];
            if (costGrid[to.first][to.second] > costGrid[node.first][node.second] + grid[to.first][to.second])
            {
                // found a better path
                costGrid[to.first][to.second] = costGrid[node.first][node.second] + grid[to.first][to.second];
                if (grid[to.first][to.second] == 0)
                    BFS_DEQ.push_front(to);
                else
                    BFS_DEQ.push_back(to);
            }
            if (costGrid[to.first][to.second] == costGrid[node.first][node.second] + grid[to.first][to.second])
                timesGrid[to.first][to.second] += timesGrid[node.first][node.second];
            //timesGrid[to.first][to.second]++;
        }
    }*/

    costGrid[start.first][start.second] = 0;
    timesGrid[start.first][start.second] = 1;
    vis[start.first][start.second] = true;
    deque<pii> BFS_DEQ;
    BFS_DEQ.push_front(start);
    pii node;
    while (!BFS_DEQ.empty())
    {
        node = BFS_DEQ.front();
        BFS_DEQ.pop_front();
        for (int i = 0; i < conns[node.first][node.second].size(); i++)
        {
            pii to = conns[node.first][node.second][i];

            //not visited yet or found a better path
            if (!vis[to.first][to.second] ||
                (costGrid[to.first][to.second] > costGrid[node.first][node.second] + grid[to.first][to.second]))
            {
                if (grid[to.first][to.second] == 0)
                    BFS_DEQ.push_front(to);
                else
                    BFS_DEQ.push_back(to);
                vis[to.first][to.second] = true;
                costGrid[to.first][to.second] = costGrid[node.first][node.second] + grid[to.first][to.second];
                timesGrid[to.first][to.second] = timesGrid[node.first][node.second];
            }
            //add the number a ways
            else if (costGrid[to.first][to.second] == costGrid[node.first][node.second] + grid[to.first][to.second])
                timesGrid[to.first][to.second] += timesGrid[node.first][node.second];
        }
    }

    /*costGrid[start.first][start.second] = 0;
    timesGrid[start.first][start.second] = 1;
    deque<pii> BFS_DEQ;
    BFS_DEQ.push_front(start);
    pii node;
    bool endVis = false;
    while (!endVis)
    {
        node = BFS_DEQ.front();
        BFS_DEQ.pop_front();
        if (node == end)
        {
            endVis = true;
            break;
        }
        for (int i = 0; i < conns[node.first][node.second].size(); i++)
        {
            pii to = conns[node.first][node.second][i];
            if (costGrid[to.first][to.second] >= costGrid[node.first][node.second] + grid[to.first][to.second])
            {
                costGrid[to.first][to.second] = costGrid[node.first][node.second] + grid[to.first][to.second];
                if (grid[to.first][to.second] == 0)
                    BFS_DEQ.push_front(to);
                else
                    BFS_DEQ.push_back(to);
            }
            if (costGrid[to.first][to.second] >= costGrid[node.first][node.second] + grid[to.first][to.second])
                //timesGrid[to.first][to.second] += timesGrid[node.first][node.second];
                timesGrid[to.first][to.second]++;
        }
    }*/

    /*costGrid[start.first][start.second] = 0;
    timesGrid[start.first][start.second] = 1;
    deque<pii_ll> BFS_DEQ;
    BFS_DEQ.push_front(make_pair(start, 0));
    pii node;
    long long prevVal, currPrevVal;
    while (!BFS_DEQ.empty())
    {
        node = BFS_DEQ.front().first;
        prevVal = BFS_DEQ.front().second;
        BFS_DEQ.pop_front();
        for (int i = 0; i < conns[node.first][node.second].size(); i++)
        {
            pii to = conns[node.first][node.second][i];
            if (costGrid[to.first][to.second] > costGrid[node.first][node.second] + grid[to.first][to.second])
            {
                currPrevVal = timesGrid[to.first][to.second];
                costGrid[to.first][to.second] = costGrid[node.first][node.second] + grid[to.first][to.second];
                if (grid[to.first][to.second] == 0)
                    BFS_DEQ.push_front(make_pair(to, currPrevVal));
                else
                    BFS_DEQ.push_back(make_pair(to, currPrevVal));
            }
            if (costGrid[to.first][to.second] >= costGrid[node.first][node.second] + grid[to.first][to.second])
                timesGrid[to.first][to.second] += timesGrid[node.first][node.second] - prevVal;
        }
    }*/

    if (costGrid[end.first][end.second] == BIG_NUM)
    {
        cout << "-1";
        return 0;
    }

    cout << costGrid[end.first][end.second] << '\n'
         << timesGrid[end.first][end.second];

    return 0;
}