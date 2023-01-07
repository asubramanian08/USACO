// Unofficial: 8:30 - 10:13
#include <iostream>
#include <algorithm>
using namespace std;
#define MAX_MASK (1 << 18)

int main(void)
{
    ios_base::sync_with_stdio(false);
    int n, g;
    cin >> n;
    bool canGo[20][20] = {0};
    for (int i = 0; i < n; i++)
    {
        bool allowedGift = true;
        for (int j = 0; j < n; j++)
        {
            cin >> g;
            if (!allowedGift)
                canGo[i][g - 1] = false;
            else
            {
                canGo[i][g - 1] = true;
                allowedGift = (g - 1 != i);
            }
        }
    }
    int DP[MAX_MASK], q, max_mask = 1 << n;
    pair<int, int> proc[MAX_MASK];
    for (int i = 0; i < max_mask; i++)
    {
        proc[i] = {0, i};
        for (int j = 0; j < n; j++)
            if (i & (1 << j))
                proc[i].first++;
    }
    sort(proc, proc + max_mask);
    cin >> q;
    while (q--)
    {
        for (int i = 0; i < max_mask; i++)
            DP[i] = 0;
        DP[0] = 1;
        int split = 0;
        char ch;
        for (int i = 0; i < n; i++)
        {
            cin >> ch;
            split = (split << 1) + (ch == 'H');
        }
        for (int i = 0; i < max_mask; i++)
        {
            int cow = proc[i].first;
            int mask = proc[i].second;
            if (DP[mask] == 0)
                continue;
            for (int j = 0; j < n; j++)
                if (canGo[cow][j] && ((mask & (1 << j)) == 0) &&
                    (((split & (1 << cow)) != 0) == ((split & (1 << j)) != 0)))
                    DP[mask ^ (1 << j)] += DP[mask];
        }
        cout << DP[max_mask - 1] << endl;
    }
    return 0;
}