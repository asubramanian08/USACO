// Start: 10:28
// Think: NA
// Write:
// Debug:
//After looking at sol: 2:11-2:34
//Rolling Hash - change easily change that has and move the string
#include <iostream>
#include <string>
#include <set>
using namespace std;

#define BIG_NUM 1000000000

int main(void)
{
    //read
#ifndef HOME
    freopen("cownomics.in", "r", stdin);
    freopen("cownomics.out", "w", stdout);
#endif
    int numCows, geneLen;
    cin >> numCows >> geneLen;
    string *spotty = new string[numCows];
    for (int i = 0; i < numCows; i++)
        cin >> spotty[i];
    string *plain = new string[numCows];
    for (int i = 0; i < numCows; i++)
        cin >> plain[i];

    //set up rolling hash
    long long *sHash = new long long[max(geneLen, numCows)];
    long long *pHash = new long long[max(geneLen, numCows)];
    long long *randL = new long long[max(geneLen, numCows)];
    for (int i = 0; i < geneLen; i++)
    {
        sHash[i] = pHash[i] = 0;
        randL[i] = rand() % BIG_NUM;
    }
    set<int> s;

    //run hash
    int start = 0, end = 0;
    bool last = false;
    int best = BIG_NUM;
    while (end < geneLen)
        if (last)
        {
            best = min(best, end - start);
            for (int i = 0; i < numCows; i++)
                s.insert(sHash[i] -= spotty[i][start] * randL[start]);
            for (int i = 0; i < numCows; i++)
                if (s.find(pHash[i] -= plain[i][start] * randL[start]) != s.end())
                    last = false;
            start++;
            s.clear();
        }
        else
        {
            last = true;
            for (int i = 0; i < numCows; i++)
                s.insert(sHash[i] += spotty[i][end] * randL[end]);
            for (int i = 0; i < numCows; i++)
                if (s.find(pHash[i] += plain[i][end] * randL[end]) != s.end())
                    last = false;
            end++;
            s.clear();
        }

    //print and delete
    cout << best << endl;
    delete[] spotty;
    delete[] plain;
    delete[] sHash;
    delete[] pHash;
    delete[] randL;
    return 0;
}