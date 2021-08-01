// Start: 11:17
// Think: 11:56
// Write: 12:10
// Debug: 12:13
#include <iostream>
#include <set>
using namespace std;

#define MOD 1000000007

int main(void)
{
    //read
#ifndef HOME
    freopen("help.in", "r", stdin);
    freopen("help.out", "w", stdout);
#endif
    int numLines;
    cin >> numLines;
    int *line = new int[numLines * 2];
    int p1, p2;
    for (int i = 0; i < numLines; i++)
    {
        cin >> p1 >> p2;
        line[p1 - 1] = i;
        line[p2 - 1] = i;
    }

    //total complexity
    long long *complexity = new long long[numLines];
    for (int i = 0; i < numLines; i++)
        complexity[i] = 0;
    set<int> on;
    for (int i = 0; i < numLines * 2; i++)
        if (on.find(line[i]) == on.end())
            on.insert(line[i]);
        else
        {
            complexity[numLines - on.size()]++;
            on.erase(line[i]);
        }

    //complexity converter
    long long *converter = new long long[numLines];
    converter[0] = 1;
    converter[1] = 2;
    for (int i = 2; i < numLines; i++)
        converter[i] = (converter[i / 2] * converter[i / 2] * converter[i % 2]) % MOD;

    //print ans with complexity and converter and delete
    long long ans = 0;
    for (int i = 0; i < numLines; i++)
        for (int j = 0; j < complexity[i]; j++)
            ans = (ans + converter[i]) % MOD;
    cout << ans << endl;
    delete[] line;
    delete[] complexity;
    delete[] converter;
    return 0;
}