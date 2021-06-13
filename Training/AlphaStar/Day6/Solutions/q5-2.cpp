/*It is also possible to optimize this solution further by keeping only two 'rows' of the DP table at a time, 
and performing mods in the solution more efficiently: */

#include <cstdio>
#include <cstring>
using namespace std;
FILE *fin = fopen("fristeam.in", "r");
FILE *fout = fopen("fristeam.out", "w");
const int MAXF = 1005, MOD = 100000000;
int N, F, R, dp[MAXF], dp2[MAXF];
inline int mod1(int a)
{
    return (a < F) ? a : a - F;
}
inline void checkmod1(int &a)
{
    if (a >= MOD)
        a -= MOD;
}
int main()
{
    fscanf(fin, "%d %d", &N, &F);
    dp[0] = dp2[0] = 1;
    for (int i = 0; i < N; i++)
    {
        fscanf(fin, "%d", &R);
        R %= F;
        for (int j = 0; j < F; j++)
            checkmod1(dp2[mod1(j + R)] += dp[j]);
        memcpy(dp, dp2, sizeof(dp));
    }
    fprintf(fout, "%d\n", (dp[0] - 1 + MOD) % MOD);
    return 0;
}