#include <iostream>
#include <string.h>
#include <stdlib.h>
using namespace std;

int main(void)
{
    // FILE *junk;
    // junk = freopen("vidgame.in", "r", stdin);
    // junk = freopen("vidgame.out", "w", stdout);
    int numConsoles, budget;
    cin >> numConsoles >> budget;
    int *best = new int[budget + 1];
    memset(best, 0, sizeof(int) * (budget + 1));
    int *from = new int[budget + 1];
    memset(from, 0, sizeof(int) * (budget + 1));
    int *to = new int[budget + 1];
    int *temp;
    int numGames, consPrice, g_price, g_produces;
    for (int i = 0; i < numConsoles; i++)
    {
        memcpy(from, best, sizeof(int) * (budget + 1));
        cin >> consPrice >> numGames;
        for (int j = 0; j < numGames; j++)
        {
            cin >> g_price >> g_produces;
            for (int k = 0; k <= budget; k++)
            {
                if (k >= g_price)
                    to[k] = max(from[k], g_produces + from[k - g_price]);
                else
                    to[k] = from[k];
            }
            temp = to;
            to = from;
            from = temp;
        }
        for (int j = consPrice; j <= budget; j++)
            best[j] = max(best[j], from[j - consPrice]);
    }
    cout << best[budget];
    return 0;
}