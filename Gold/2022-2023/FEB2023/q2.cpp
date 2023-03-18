// Official:
#pragma GCC optimize("Ofast")
#pragma GCC target("avx2")
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

#define N 200010
int n, rate[N], parent, depth;
vector<int> tree[N];
struct trip
{
    int time, rate, cost, enderCost;
};

int findDepth(int node)
{
    int ans = 0;
    for (int next : tree[node])
        ans = max(ans, findDepth(next) + 1);
    return ans;
}

int findCost(const vector<trip> &trips)
{
    int cost = 0, time = 0;
    for (trip t : trips)
    {
        cost += t.rate * time + t.cost;
        time += t.time;
    }
    return cost;
}

trip DFS(int node, int d)
{
    trip ans = {0, rate[node], 0, d == depth ? 0 : -1};
    vector<trip> trips;
    auto compare = [](const trip &t1, const trip &t2)
    { return t1.time * t2.cost < t2.time * t1.cost; };
    for (int next : tree[node])
    {
        trips.push_back(DFS(next, d + 1));
        ans.time += (trips.back().time += 2);
        ans.rate += trips.back().rate;
        trips.back().cost += trips.back().rate;
        if (trips.back().enderCost != -1)
            trips.back().enderCost += trips.back().rate;
    }
    int toEnd = -1, cost;
    for (int i = 0; i < trips.size(); i++)
        if (int myCost = (ans.time - trips[i].time) * trips[i].rate;
            trips[i].enderCost != -1 && (toEnd == -1 || myCost < cost))
            toEnd = i, cost = myCost;
    if (toEnd != -1)
    {
        swap(trips[toEnd], trips[trips.size() - 1]);
        sort(trips.begin(), prev(trips.end()), compare);
        ans.enderCost = findCost(trips) - trips.back().cost + trips.back().enderCost;
    }
    sort(trips.begin(), trips.end(), compare);
    ans.cost = findCost(trips);
    return ans;
}

int main(void)
{
    ios_base::sync_with_stdio(false);
    bool t;
    cin >> n >> t;
    for (int i = 1; i < n; i++)
    {
        cin >> parent >> rate[i];
        tree[parent - 1].push_back(i);
    }
    depth = t ? findDepth(0) : n + 1;
    cout << (n - 1) * 2 - (t ? depth : 0) << ' ';
    cout << (t ? DFS(0, 0).enderCost : DFS(0, 0).cost) << endl;
    return 0;
}