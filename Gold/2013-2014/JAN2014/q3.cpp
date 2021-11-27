// Start: 9:58
// Think: 10:35
// Write: 11:16
// Debug: 11:31
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// DSU or union-find
class DSU
{
private:
    int *id, *sz, *starts;

public:
    DSU(int n_ele, int *st);
    int root(int idx); // find its first parent
    bool is_connected(int n1, int n2) { return root(n1) == root(n2); }
    void connect(int n1, int n2);
    int getStart(int idx) { return starts[root(idx)]; }
    void changeStart(int idx, int change) { starts[root(idx)] = change; }
    int getSize(int idx) { return sz[root(idx)]; }
    ~DSU();
};
DSU::DSU(int n_ele, int *st)
{
    id = new int[n_ele];
    sz = new int[n_ele];
    for (int i = 0; i < n_ele; i++)
    {
        id[i] = i;
        sz[i] = 1;
    }
    starts = st;
}
int DSU::root(int idx)
{
    while (idx != id[idx])
    {
        id[idx] = id[id[idx]];
        idx = id[idx];
    }
    return idx;
}
void DSU::connect(int n1, int n2)
{
    int i = root(n1), j = root(n2);
    if (i == j)
        return;
    starts[i] = starts[j] = starts[i] + starts[j];
    if (sz[i] < sz[j])
    {
        id[i] = j;
        sz[j] += sz[i];
    }
    else
    {
        id[j] = i;
        sz[i] += sz[j];
    }
}
DSU::~DSU()
{
    delete[] id;
    delete[] sz;
}

int main(void)
{
    // read
    //#ifndef HOME
    freopen("skilevel.in", "r", stdin);
    freopen("skilevel.out", "w", stdout);
    //#endif
    int rows, cols, minCells;
    cin >> rows >> cols >> minCells;
    int *height = new int[rows * cols];
    for (int i = 0; i < rows * cols; i++)
        cin >> height[i];
    int *is_start = new int[rows * cols];
    for (int i = 0; i < rows * cols; i++)
        cin >> is_start[i];

    // connections of adjacent nodes
    using pii = pair<int, int>;
    vector<pair<long long, pii>> connections;
    for (int i = 0; i < rows * cols; i++)
    {
        if (i % cols != cols - 1)
            connections.push_back(make_pair(abs(height[i] - height[i + 1]), pii(i, i + 1)));
        if (i + cols < rows * cols)
            connections.push_back(make_pair(abs(height[i] - height[i + cols]), pii(i, i + cols)));
    }
    sort(connections.begin(), connections.end());

    // and edges to DSU
    long long total_difficulty = 0;
    DSU course(rows * cols, is_start);
    for (auto connection : connections)
    {
        course.connect(connection.second.first, connection.second.second);
        if (course.getSize(connection.second.first) >= minCells)
        {
            total_difficulty += course.getStart(connection.second.first) * connection.first;
            course.changeStart(connection.second.first, 0);
        }
    }

    // print and delete
    cout << total_difficulty << endl;
    delete[] height;
    delete[] is_start;
    return 0;
}