// Official: 5 / 20
#include <iostream>
#include <queue>
using namespace std;
#define MAX_STATE (1 << 12)
#define BIG_NUM 1000000000
using pii = pair<int, int>;

int main(void)
{
    ios_base::sync_with_stdio(false);
    int t, n;
    cin >> t >> n;
    int DP[MAX_STATE][MAX_STATE];
    int states = (1 << n);
    queue<pii> q;
    for (int i = 0; i < states; i++)
    {
        DP[0][i] = 0;
        q.push({0, i});
    }
    for (int i = 1; i < states; i++)
        for (int j = 0; j < states; j++)
            DP[i][j] = BIG_NUM;
    while (!q.empty())
    {
        pii pos = q.front();
        q.pop();
        if (pos == pii(256, 264))
            int hi = 0;
        int tempSwitches = (pos.second << 1) & ((1 << n) - 1);
        if (pos.second & (1 << (n - 1)))
            tempSwitches++;
        int newLights = pos.first ^ tempSwitches;
        for (int i = 0; i < n; i++)
            if (int newSwitches = tempSwitches ^ (1 << i);
                DP[newLights][newSwitches] == BIG_NUM)
            {
                DP[newLights][newSwitches] = DP[pos.first][pos.second] + 1;
                q.push({newLights, newSwitches});
            }
    }

    for (int i = 0; i < t; i++)
    {
        char ch;
        int lights = 0, switches = 0;
        for (int j = 0; j < n; j++)
        {
            cin >> ch;
            lights = lights * 2 + (ch - '0');
        }
        for (int j = 0; j < n; j++)
        {
            cin >> ch;
            switches = switches * 2 + (ch - '0');
        }
        cout << DP[lights][switches] << endl;
    }
    return 0;
}