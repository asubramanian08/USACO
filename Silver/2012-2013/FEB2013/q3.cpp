//Also in Starleague Part 1 lesson 9 q1
// Start: 10:01
// Think: 10:09
// Write: 10:28
// Debug: 10:29
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
using namespace std;

int main(void)
{
    //read
#ifndef HOME
    freopen("msched.in", "r", stdin);
    freopen("msched.out", "w", stdout);
#endif
    int numCows, numDepend;
    cin >> numCows >> numDepend;
    int *milkTime = new int[numCows];
    for (int i = 0; i < numCows; i++)
        cin >> milkTime[i];
    vector<int> *controls = new vector<int>[numCows];
    int *cowDepend = new int[numCows];
    fill(cowDepend, cowDepend + numCows, 0);
    int A, B;
    for (int i = 0; i < numDepend; i++)
    {
        cin >> A >> B;
        A--;
        B--;
        controls[A].push_back(B);
        cowDepend[B]++;
    }
    int *startTime = new int[numCows];
    fill(startTime, startTime + numCows, 0);

    //do the augmented BFS
    queue<int> toVis;
    for (int i = 0; i < numCows; i++)
        if (cowDepend[i] == 0)
            toVis.push(i);
    int currCow;
    while (!toVis.empty())
    {
        currCow = toVis.front();
        toVis.pop();
        for (int fixCow : controls[currCow])
        {
            startTime[fixCow] = max(startTime[fixCow], startTime[currCow] + milkTime[currCow]);
            cowDepend[fixCow]--;
            if (cowDepend[fixCow] == 0)
                toVis.push(fixCow);
        }
    }

    //print and delete
    int maxTime = 0;
    for (int i = 0; i < numCows; i++)
        maxTime = max(maxTime, startTime[i] + milkTime[i]);
    cout << maxTime;
    delete[] milkTime;
    delete[] cowDepend;
    delete[] startTime;
    return 0;
}