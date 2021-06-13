#include <iostream>
using namespace std;

#define BIG_NUM 100000
int main(void)
{
    /*FILE *junk;
    junk = freopen("taming.in", "r", stdin);
    junk = freopen("taming.out", "w", stdout);*/
    //set up
    int days;
    cin >> days;
    int *log = new int[days];
    for (int i = 0; i < days; i++)
        cin >> log[i];
    //DP[i] = have i + 1 break outs left over
    int **DP = new int *[days];
    for (int i = 0; i < days; i++)
        DP[i] = new int[days];

    //fill DP
    for (int i = 0; i < days; i++)
        for (int j = days - 1; j >= 0; j--)
        {
            DP[i][j] = 0;
            int minCost = BIG_NUM, logCost = 0;
            for (int k = j; k < days - i; k++)
            {
                logCost += log[k] != (k - j);
                if (i != 0)
                    minCost = min(minCost, logCost + DP[i - 1][k + 1]);
                else
                    minCost = logCost;
            }
            DP[i][j] = minCost;
        }

    //print output
    for (int i = 0; i < days; i++)
        cout << DP[i][0] << '\n';
    return 0;
}