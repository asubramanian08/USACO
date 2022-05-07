#include <iostream>
#include <string>
using namespace std;
#define MAX_COMMANDS 2005
#define MOD 1000000007

int main(void)
{
    int tests, commands;
    cin >> tests;
    long long DPvarSum[MAX_COMMANDS][MAX_COMMANDS];
    long long DPconstSum[MAX_COMMANDS][MAX_COMMANDS];
    for (int test = 0; test < tests; test++)
    {
        cin >> commands;
        string prog1, prog2;
        cin >> prog1 >> prog2;
        int start1 = 0, start2 = 0;
        for (int i = 0; i < commands; i++)
        {
            start1 = prog1[i] == '0' ? i : start1;
            start2 = prog2[i] == '0' ? i : start2;
        }
        DPvarSum[start1][start2] = DPconstSum[start1][start2] = 1;
        for (int i = start1 + 1; i < commands; i++)
        {
        }
    }
    return 0;
}