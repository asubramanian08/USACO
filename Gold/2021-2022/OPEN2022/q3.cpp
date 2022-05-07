#include <iostream>
#include <vector>
using namespace std;
using pii = pair<int, int>;

int closestTo(int goal, pii range)
{
    if (goal < range.first)
        return range.first;
    else if (goal > range.second)
        return range.second;
    else
        return goal;
}

void updateRange(pii &range, int add)
{
    if (add < range.first)
        range.first = add;
    if (add > range.second)
        range.second = add;
}

int setValues(int *bestValue, vector<int> *tree, pii ansRange, pii *ranges, int node, int par)
{
    bestValue[node] = closestTo(ansRange.first, ranges[node]);
    updateRange(ansRange, bestValue[node]);
    int ret = ansRange.second - ansRange.first;
    for (int next : tree[node])
        if (next != par)
            ret = max(ret, setValues(bestValue, tree, ansRange, ranges, next, node));
    return ret;
}

int main(void)
{
    // read
    int tests, printTree;
    cin >> tests >> printTree;
    for (int test = 0; test < tests; test++)
    {
        int numNodes, par;
        cin >> numNodes;
        vector<int> *tree = new vector<int>[numNodes];
        for (int i = 1; i < numNodes; i++)
        {
            cin >> par;
            tree[par - 1].push_back(i);
        }
        pii *ranges = new pii[numNodes];
        for (int i = 0; i < numNodes; i++)
            cin >> ranges[i].first >> ranges[i].second;

        // root value: (highestLow + lowestHigh) / 2
        int highestLow = ranges[0].first, lowestHigh = ranges[0].second;
        for (int i = 1; i < numNodes; i++)
        {
            highestLow = max(highestLow, ranges[i].first);
            lowestHigh = min(lowestHigh, ranges[i].second);
        }
        int bestRoot = closestTo((highestLow + lowestHigh) / 2, ranges[0]);

        // DFS best values on tree
        int *bestValue = new int[numNodes];
        int ans = setValues(bestValue, tree, pii(bestRoot, bestRoot), ranges, 0, -1);

        // print and delete
        cout << ans << endl;
        if (printTree)
        {
            for (int i = 0; i < numNodes; i++)
            {
                cout << bestValue[i];
                if (i < numNodes - 1)
                    cout << ' ';
            }
            cout << endl;
        }
        delete[] tree;
        delete[] ranges;
        delete[] bestValue;
    }
    return 0;
}