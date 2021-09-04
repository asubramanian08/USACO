// Start: 11:06
// Think: 11:15?
// Write: 11:46
// Debug: 12:20
#include <iostream>
#include <queue>
using namespace std;

using pii = pair<int, int>;
struct to
{
    int time, feildNum;
    pii feild;
    bool operator>(const to &t) const { return time > t.time; }
    to(int time, int feildNum, pii feild) : time(time), feildNum(feildNum), feild(feild) {}
};
#define MAX_SIDE 110
int grass[MAX_SIDE][MAX_SIDE];
bool vis[MAX_SIDE][MAX_SIDE][3] = {false};
#define BIG_NUM 1000000000

int main(void)
{
    //read
#ifndef HOME
    freopen("visitfj.in", "r", stdin);
    freopen("visitfj.out", "w", stdout);
#endif
    int sideLen, crossTime;
    cin >> sideLen >> crossTime;
    for (int i = 0; i < sideLen; i++)
        for (int j = 0; j < sideLen; j++)
            cin >> grass[i][j];

    //dijkstras
    priority_queue<to, vector<to>, greater<to>> pq;
    auto add = [&pq, sideLen](int time, int feildNum, pii pos)
    {
        if (pos.first >= 0 && pos.first < sideLen && pos.second >= 0 && pos.second < sideLen &&
            !vis[pos.first][pos.second][feildNum % 3])
            pq.push(to(time + (feildNum % 3 == 0 ? grass[pos.first][pos.second] : 0), feildNum, pos));
    };
    pq.push(to(0, 0, {0, 0}));
    int ans = BIG_NUM;
    while (!pq.empty())
    {
        to curr = pq.top();
        pq.pop();
        if (vis[curr.feild.first][curr.feild.second][curr.feildNum % 3])
            continue;
        vis[curr.feild.first][curr.feild.second][curr.feildNum % 3] = true;
        if (curr.feild.first == sideLen - 1 && curr.feild.second == sideLen - 1)
            ans = min(ans, curr.time);
        add(curr.time + crossTime, curr.feildNum + 1, {curr.feild.first + 1, curr.feild.second});
        add(curr.time + crossTime, curr.feildNum + 1, {curr.feild.first, curr.feild.second + 1});
        add(curr.time + crossTime, curr.feildNum + 1, {curr.feild.first - 1, curr.feild.second});
        add(curr.time + crossTime, curr.feildNum + 1, {curr.feild.first, curr.feild.second - 1});
    }

    //print
    cout << ans << endl;
    return 0;
}