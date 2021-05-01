// Start: 8:18
// Think: before 8:37
// Write: 8:44, 9:18 - 10:22!
// Debug: 10:24
#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main(void)
{
    //read
#ifndef HOME
    freopen("cowids.in", "r", stdin);
    freopen("cowids.out", "w", stdout);
#endif
    int label, oneBits;
    cin >> label >> oneBits;

    //find the number of labels in ...
    vector<int> *DP = new vector<int>[oneBits + 1];
    DP[0].push_back(1);
    for (int i = 1; i <= oneBits; i++)
        DP[i].push_back(0);
    for (int i = 1; DP[oneBits][i - 1] < label; i++)
    {
        DP[0].push_back(1);
        for (int j = 1; j <= oneBits; j++)
            DP[j].push_back(DP[j - 1][i - 1] + DP[j][i - 1]);
    }

    //print
    string ans;
    for (int binLen = DP[oneBits].size() - 2; binLen >= 0; binLen--)
        if (DP[oneBits][binLen] < label)
        {
            ans += '1';
            label -= DP[oneBits][binLen];
            oneBits--;
        }
        else
            ans += '0';
    cout << ans << '\n';
    return 0;
}