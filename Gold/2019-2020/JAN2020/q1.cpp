// Start: 9:18
// Think: 9:32, 1:53-2:00
// Write: 2:13
// Debug:
#include <iostream>
#include <vector>
using namespace std;

#define MAX_NODES 1000
#define MAX_TIME 1000
int DP[MAX_NODES][MAX_TIME + 1];
#define NA -1

int main(void)
{
    //read
#ifndef HOME
    freopen("time.in", "r", stdin);
    freopen("time.out", "w", stdout);
#endif
    int numCities, numPaths, timeCost;
    cin >> numCities >> numPaths >> timeCost;
    int *earn = new int[numCities];
    for (int i = 0; i < numCities; i++)
        cin >> earn[i];
    int n1, n2;
    vector<int> *graph = new vector<int>[numCities];
    for (int i = 0; i < numPaths; i++)
    {
        cin >> n1 >> n2;
        graph[n1 - 1].push_back(n2 - 1);
    }

    //earning at each time
    for (int i = 0; i < numCities; i++)
        DP[i][0] = NA;
    DP[0][0] = 0;
    for (int time = 0; time < MAX_TIME; time++)
    {
        for (int i = 0; i < numCities; i++)
            DP[i][time + 1] = NA;
        for (int node = 0; node < numCities; node++)
            if (DP[node][time] != NA)
                for (int next : graph[node])
                    DP[next][time + 1] = max(DP[next][time + 1], DP[node][time] + earn[next]);
    }

    //print and delete
    int best = 0;
    for (int i = 0; i < MAX_TIME; i++)
        best = max(best, DP[0][i] - timeCost * i * i);
    cout << best;
    delete[] earn;
    delete[] graph;
    return 0;
}