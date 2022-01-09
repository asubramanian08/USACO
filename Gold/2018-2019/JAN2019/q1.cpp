// Start: 4:57
// Think: 5:09
// Write: 5:42
// Debug: 6:00
#include <iostream>
#include <algorithm>
using namespace std;

#define MOD 1000000007
long long pow(long long num, long long exp)
{
    if (exp == 1)
        return num;
    if (exp == 0)
        return 0; // purposeful
    long long ans = pow(num, exp / 2);
    ans = (ans * ans) % MOD;
    if (exp % 2 == 1)
        ans = (ans * num) % MOD;
    return ans;
}

int main(void)
{
    // read
#ifndef HOME
    freopen("poetry.in", "r", stdin);
    freopen("poetry.out", "w", stdout);
#endif
    int numWords, lines, syllables;
    cin >> numWords >> lines >> syllables;
    using pii = pair<int, int>;
    pii *words = new pii[numWords];
    for (int i = 0; i < numWords; i++)
        cin >> words[i].first >> words[i].second;
    int *scheme = new int[26];
    for (int i = 0; i < lines; i++)
    {
        char rhyme;
        cin >> rhyme;
        scheme[rhyme - 'A']++;
    }

    // ways to finish a line
    long long *finishLine = new long long[syllables];
    fill(finishLine, finishLine + syllables, 0);
    finishLine[0] = 1;
    for (int j = 0; j < syllables; j++)
        for (int i = 0; i < numWords; i++)
            if (j + words[i].first < syllables)
                finishLine[j + words[i].first] = (finishLine[j + words[i].first] + finishLine[j]) % MOD;

    // way in a rhyme class
    long long *rhymeClass = new long long[numWords];
    fill(rhymeClass, rhymeClass + numWords, 0);
    for (int i = 0; i < numWords; i++)
    {
        rhymeClass[words[i].second - 1] += finishLine[syllables - words[i].first];
        rhymeClass[words[i].second - 1] = rhymeClass[words[i].second - 1] % MOD;
    }

    // ways to fill a letter
    long long ans = 1, curr;
    for (int i = 0; i < 26; i++)
    {
        curr = 0;
        for (int j = 0; j < numWords; j++)
            curr = (curr + pow(rhymeClass[j], scheme[i])) % MOD;
        if (curr == 0)
            curr = 1;
        ans = (ans * curr) % MOD;
    }

    // print and delete
    cout << ans << endl;
    delete[] words;
    delete[] scheme;
    delete[] finishLine;
    delete[] rhymeClass;
    return 0;
}