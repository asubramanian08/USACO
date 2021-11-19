// Start: 11:34
// Think: 11:47, 12:23-1:23
// Write: 1:50
// Debug: 2:30
#include <iostream>
#include <vector>
#include <set>
#include <map>
using namespace std;

#define MAX_SIDE 750
#define MOD 1000000007
int rows, cols, colors;

// BIT or fenwick tree
class BIT
{
private:
    int *bTree;
    int elements;

public:
    BIT();
    ~BIT() { delete[] bTree; }
    int query(int node);
    void updt(int node, int cng);
};
BIT::BIT()
{
    elements = cols;
    bTree = new int[elements + 1];
    for (int i = 1; i <= elements; i++)
        bTree[i] = 0;
}
int BIT::query(int node)
{
    if (node == -1)
        return 0;
    int sum = 0;
    for (int i = node + 1; i > 0; i -= (i & -i))
        sum = (sum + bTree[i]) % MOD;
    return sum;
}
void BIT::updt(int node, int cng)
{
    for (int i = node + 1; i <= elements; i += (i & -i))
        bTree[i] = (bTree[i] + cng) % MOD;
}

int main(void)
{
    // read
#ifndef HOME
    freopen("hopscotch.in", "r", stdin);
    freopen("hopscotch.out", "w", stdout);
#endif
    cin >> rows >> cols >> colors;
    int grid[MAX_SIDE][MAX_SIDE];
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
        {
            cin >> grid[i][j];
            grid[i][j]--;
        }

    // remove unused colors
    set<int> used;
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            used.insert(grid[i][j]);
    map<int, int> change;
    int pos = -1;
    for (int color : used)
        change[color] = ++pos;
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            grid[i][j] = change[grid[i][j]];
    colors = used.size();

    // setup
    BIT *colored = new BIT[colors];
    BIT all;
    all.updt(0, 1);
    colored[grid[0][0]].updt(0, 1);
    int *toSet = new int[cols];
    toSet[0] = 0;

    // run (imaginary DP)
    for (int i = 1; i < rows; i++)
    {
        for (int j = 1; j < cols; j++)
            toSet[j] = (all.query(j - 1) - colored[grid[i][j]].query(j - 1) + MOD) % MOD;
        for (int j = 1; j < cols; j++)
        {
            all.updt(j, toSet[j]);
            colored[grid[i][j]].updt(j, toSet[j]);
        }
    }

    // print and delete
    cout << toSet[cols - 1] << endl;
    delete[] toSet;
    return 0;
}