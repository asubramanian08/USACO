// Start: 9:58
// Think: 10:11
// Write: 10:41
// Debug: 11:03
#include <iostream>
using namespace std;

#define MAX_SIZE 1001
int DP[MAX_SIZE][MAX_SIZE]; //DP[pos][cowType]
int active[MAX_SIZE];
#define MOD 2012

bool is_bal(string para)
{
    int on = 0;
    for (int i = 0; i < para.size(); i++)
    {
        active[i] = on;
        on += para[i] == '(' ? 1 : -1;
        if (on < 0)
            return false;
    }
    return on == 0;
}

int main(void)
{
    //read
#ifndef HOME
    freopen("bbreeds.in", "r", stdin);
    freopen("bbreeds.out", "w", stdout);
#endif
    string para;
    cin >> para;
    if (!is_bal(para))
    {
        cout << '0';
        return 0;
    }

    //do the DP
    int length = para.size();
    for (int i = 0; i < MAX_SIZE; i++)
        DP[length][i] = (i == 0);
    for (int i = length - 1; i >= 0; i--)
        for (int j = 0; j <= active[i]; j++)
        {
            DP[i][j] = DP[i + 1][j];
            if (para[i] == ')' && j == active[i])
                DP[i][j] = 0;

            if (para[i] == '(')
                DP[i][j] += DP[i + 1][j + 1];
            else if (para[i] == ')' && j != 0)
                DP[i][j] += DP[i + 1][j - 1];
            DP[i][j] %= MOD;
        }

    //print
    cout << DP[0][0];
    return 0;
}