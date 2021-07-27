// Start: 5:57
// Think: 6:18
// Write:
// Debug:
// After looking at sol: 3:25-4:07
#include <iostream>
#include <string>
using namespace std;

#define MOD 1000000007
#define LETTERS 4
#define MAX_LEN 100010
//     index,   f of sl, f of l,  l of l
int DP[MAX_LEN][LETTERS][LETTERS][LETTERS] = {0};
// 1st(char pos): first(f) or last(l)
// 2nd(section): second to last(sl), last(l)
char convert[] = "AGCT";
#define WILD '?'

int main(void)
{
    //read
    string str;
    cin >> str;

    //initial possibilities
    for (int fsl = 0; fsl < LETTERS; fsl++)
        for (int ll = 0; ll < LETTERS; ll++)
            if (str[0] == WILD || str[0] == convert[ll])
                DP[0][fsl][ll][ll] = 1;

    //run DP going index by index
    for (int idx = 1; idx < str.size(); idx++)
        for (int ll = 0; ll < LETTERS; ll++)
            if (str[idx] == WILD || str[idx] == convert[ll])
                for (int fsl = 0; fsl < LETTERS; fsl++)
                    for (int fl = 0; fl < LETTERS; fl++)
                        for (int p_ll = 0; p_ll < LETTERS; p_ll++)
                        {
                            if (ll != p_ll) //continue making string
                            {
                                DP[idx][fsl][fl][ll] += DP[idx - 1][fsl][fl][p_ll];
                                DP[idx][fsl][fl][ll] %= MOD;
                            }
                            if (fsl == p_ll) //potential flip
                            {
                                DP[idx][fl][ll][ll] += DP[idx - 1][fsl][fl][p_ll];
                                DP[idx][fl][ll][ll] %= MOD;
                            }
                        }

    //find the answer
    int ans = 0;
    for (int fl = 0; fl < LETTERS; fl++)
        for (int ll = 0; ll < LETTERS; ll++)
        {
            ans += DP[str.size() - 1][ll][fl][ll];
            ans %= MOD;
        }
    cout << ans << endl;
    return 0;
}