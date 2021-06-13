#include <iostream>
using namespace std;

#define MOD 9901
long long **DP;
void findVal(int nodes, int height)
{
    if (DP[nodes][height])
        return;
    long long ans = 0;
    nodes--;  //For the
    height--; //Root node
    for (int i = 1; i < nodes; i++)
        if (DP[i][height])
            for (int j = 1; j <= height; j++)
                if (DP[nodes - i][j])
                {
                    if (j == height)
                        ans += DP[i][height] * DP[nodes - i][j];
                    else
                        ans += 2 * DP[i][height] * DP[nodes - i][j];
                    ans = ans % MOD;
                }
    DP[nodes + 1][height + 1] = ans;
}
int main(void)
{
    /*FILE *junk;
    junk = freopen("nocows.in", "r", stdin);
    junk = freopen("nocows.out", "w", stdout);*/

    int nodes, height;
    cin >> nodes >> height;
    DP = new long long *[nodes + 1];
    for (int i = 0; i <= nodes; i++)
        DP[i] = new long long[height + 1];

    for (int i = 0; i <= nodes; i++)
        for (int j = 0; j <= height; j++)
            DP[i][j] = 0;

    DP[1][1] = 1;
    for (int i = 1; i <= nodes; i++)
        for (int j = 1; j <= height; j++)
            findVal(i, j);
    cout << DP[nodes][height];
    return 0;
}