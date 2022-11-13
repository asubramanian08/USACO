// Unofficial: 11:20 - 12:15
#include <iostream>
#include <string>
#include <map>
using namespace std;
#define LEN 20

int main(void)
{
    string str;
    cin >> str;
    map<char, char> m;
    for (int i = 0; i < str.size(); i++)
    {
        if (m.find(str[i]) == m.end())
            m[str[i]] = m.size() + 'a';
        str[i] = m[str[i]];
    }
    int next[LEN][LEN] = {{0}};
    for (int i = 1; i < str.size(); i++)
        next[str[i - 1] - 'a'][str[i] - 'a']++;
    int DP[1 << LEN] = {1};
    for (int i = 0; i < 1 << LEN; i++)
        for (int j = 0; j < LEN; j++)
            if (int to = i | (1 << j); to != i)
            {
                if (DP[to] == 0)
                    DP[to] = 1'000'000'000;
                int cost = DP[i];
                for (int k = 0; k < LEN; k++)
                    if (to & (1 << k))
                        cost += next[j][k];
                DP[to] = min(DP[to], cost);
            }
    cout << DP[(1 << LEN) - 1] << endl;
    return 0;
}