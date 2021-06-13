#include <iostream>
#include <vector>
#include <deque>
#include <string.h>
using namespace std;

#define BIG_NUM 10000000
typedef pair<int, int> pii;
struct point
{
    int x, y, orig;
};
struct post
{
    int dir[4];
};

int xCompare(const void *p1, const void *p2)
{
    int returnVal = ((point *)p1)->x - ((point *)p2)->x;
    if (returnVal == 0)
        returnVal = ((point *)p1)->y - ((point *)p2)->y;
    return returnVal;
}
int yCompare(const void *p1, const void *p2)
{
    int returnVal = ((point *)p1)->y - ((point *)p2)->y;
    if (returnVal == 0)
        returnVal = ((point *)p1)->x - ((point *)p2)->x;
    return returnVal;
}
int main(void)
{
    /*FILE *junk;
    junk = freopen("lasers.in", "r", stdin);
    junk = freopen("lasers.out", "w", stdout);*/
    point start, end;
    int numPoles;
    cin >> numPoles >> start.x >> start.y >> end.x >> end.y;
    numPoles += 2; // start and end
    point *poles = new point[numPoles];
    for (int i = 0; i < numPoles - 2; i++)
    {
        cin >> poles[i].x >> poles[i].y;
        poles[i].orig = i;
    }
    poles[numPoles - 2].x = start.x;
    poles[numPoles - 2].y = start.y;
    poles[numPoles - 2].orig = numPoles - 2;
    poles[numPoles - 1].x = end.x;
    poles[numPoles - 1].y = end.y;
    poles[numPoles - 1].orig = numPoles - 1;

    point *by_x = new point[numPoles];
    memcpy(by_x, poles, numPoles * sizeof(point));
    qsort(by_x, numPoles, sizeof(point), xCompare);
    point *by_y = new point[numPoles];
    memcpy(by_y, poles, numPoles * sizeof(point));
    qsort(by_y, numPoles, sizeof(point), yCompare);

    point *comesFrom = new point[numPoles];
    for (int i = 0; i < numPoles; i++)
    {
        comesFrom[by_x[i].orig].x = i;
        comesFrom[by_y[i].orig].y = i;
    }
    post *graph = new post[numPoles];
    for (int i = 0; i < numPoles; i++)
    {
        if (comesFrom[i].x + 1 != numPoles)
        {
            graph[i].dir[0] = by_x[comesFrom[i].x + 1].orig;
            if (poles[graph[i].dir[0]].x != poles[i].x)
                graph[i].dir[0] = BIG_NUM;
        }
        else
            graph[i].dir[0] = BIG_NUM;

        if (comesFrom[i].y + 1 != numPoles)
        {
            graph[i].dir[1] = by_y[comesFrom[i].y + 1].orig;
            if (poles[graph[i].dir[1]].y != poles[i].y)
                graph[i].dir[1] = BIG_NUM;
        }
        else
            graph[i].dir[1] = BIG_NUM;

        if (comesFrom[i].x - 1 != -1)
        {
            graph[i].dir[2] = by_x[comesFrom[i].x - 1].orig;
            if (poles[graph[i].dir[2]].x != poles[i].x)
                graph[i].dir[2] = BIG_NUM;
        }
        else
            graph[i].dir[2] = BIG_NUM;

        if (comesFrom[i].y - 1 != -1)
        {
            graph[i].dir[3] = by_y[comesFrom[i].y - 1].orig;
            if (poles[graph[i].dir[3]].y != poles[i].y)
                graph[i].dir[3] = BIG_NUM;
        }
        else
            graph[i].dir[3] = BIG_NUM;
    }

    deque<pii> BFS;
    //second - direction: 0 = up, 1 = right, 2 = down, 3 = left
    BFS.push_front(make_pair(graph[numPoles - 2].dir[0], 0));
    BFS.push_front(make_pair(graph[numPoles - 2].dir[1], 1));
    BFS.push_front(make_pair(graph[numPoles - 2].dir[2], 2));
    BFS.push_front(make_pair(graph[numPoles - 2].dir[3], 3));
    pii node;
    post *ansArr = new post[numPoles];
    for (int i = 0; i < numPoles; i++)
        for (int j = 0; j < 4; j++)
            ansArr[i].dir[j] = BIG_NUM;
    for (int i = 0; i < 4; i++)
        ansArr[numPoles - 2].dir[i] = 0;
    while (!BFS.empty())
    {
        node = BFS.front();
        BFS.pop_front();
        if (node.first == BIG_NUM)
            continue;
        int setVal = ansArr[graph[node.first].dir[(node.second + 2) % 4]].dir[node.second];

        //is the end
        if (node.first == numPoles - 1)
        {
            ansArr[node.first].dir[node.second] = setVal;
            continue;
        }

        //same direction
        if ((graph[node.first].dir[node.second] != BIG_NUM) &&
            (ansArr[node.first].dir[node.second] > setVal))
        {
            BFS.push_front(make_pair(graph[node.first].dir[node.second], node.second));
            ansArr[node.first].dir[node.second] = setVal;
        }

        //switch one
        if ((graph[node.first].dir[(node.second + 1) % 4] != BIG_NUM) &&
            (ansArr[node.first].dir[(node.second + 1) % 4] > setVal + 1))
        {
            BFS.push_back(make_pair(graph[node.first].dir[(node.second + 1) % 4], (node.second + 1) % 4));
            ansArr[node.first].dir[(node.second + 1) % 4] = setVal + 1;
        }

        //switch two
        if ((graph[node.first].dir[(node.second + 3) % 4] != BIG_NUM) &&
            (ansArr[node.first].dir[(node.second + 3) % 4] > setVal + 3))
        {
            BFS.push_back(make_pair(graph[node.first].dir[(node.second + 3) % 4], (node.second + 3) % 4));
            ansArr[node.first].dir[(node.second + 3) % 4] = setVal + 1;
        }
    }
    int ans = min(min(ansArr[numPoles - 1].dir[0], ansArr[numPoles - 1].dir[1]),
                  min(ansArr[numPoles - 1].dir[2], ansArr[numPoles - 1].dir[3]));
    if (ans == BIG_NUM)
        cout << "-1";
    else
        cout << ans;
    return 0;
}