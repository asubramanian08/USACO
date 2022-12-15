// Unofficial: 7:00 - 7:40
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

long long n, arr[100010], value[100010], extra;
vector<int> *graph;
int findHeight(int node)
{
    int height = 0;
    for (int next : graph[node])
        height = max(height, findHeight(next) + 1);
    return height;
}
void DFS(int node, long long height)
{
    value[node] = height * (n + 1) + extra--;
    sort(graph[node].begin(), graph[node].end(), greater<int>());
    for (int next : graph[node])
        DFS(next, height - 1);
}

int main(void)
{
    cin >> n;
    for (int i = 0; i < n; i++)
        cin >> arr[i];
    graph = new vector<int>[n + 1];
    for (int i = 0; i < n; i++)
        graph[arr[i]].push_back(i);
    cout << n + 1 << endl; // k = n + 1
    extra = n;
    DFS(n, findHeight(n));
    for (int i = 0; i < n; i++)
        cout << value[i] << endl;
    return 0;
}