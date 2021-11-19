// Start: 11:47
// Think: 11:58
// Write:
// Debug:
// After looking at sol:
#include <iostream>
#include <map>
#include <set>
#include <string>
using namespace std;

#define BASE 29
#define MOD 1000000007
#define NA -1
int main(void)
{
    // read
#ifndef HOME
    freopen("censor.in", "r", stdin);
    freopen("censor.out", "w", stdout);
#endif
    string text;
    int removeSize, maxLen = 0;
    cin >> text >> removeSize;
    string *remove = new string[removeSize];
    for (int i = 0; i < removeSize; i++)
    {
        cin >> remove[i];
        maxLen = max(maxLen, (int)remove[i].size());
    }

    // linked list - text based
    int *next = new int[text.size()];
    int *prev = new int[text.size()];
    for (int i = 0; i < text.size(); i++)
    {
        next[i] = i == text.size() - 1 ? NA : i + 1;
        prev[i] = i == 0 ? NA : i - 1;
    }
    auto delsstr = [next, prev](int start, int end)
    {
        if (prev[start] != NA)
            next[prev[start]] = next[end];
        if (next[end] != NA)
            prev[next[end]] = prev[start];
        prev[start] = 0; // not NA -> can't be start of linked list
    };

    // hash functions: rehash, nextHash, remove strings' hashes
    auto rehash = [&](int &start, int &end, int size)
    {
        start = end;
        for (int i = 1; i < size; i++)
            if (prev[start] != NA)
                start = prev[start];
        long long hash = 0;
        for (int iter = start, i = 0; i < size; i++, iter = next[iter])
        {
            if (iter == NA)
                return (long long)NA;
            hash = (hash + text[iter] - 'a') % MOD;
            hash = (hash * BASE) % MOD;
            end = iter; // set end (to early end)
        }
        return hash;
    };
    long long *powMod = new long long[maxLen + 1];
    powMod[0] = 1;
    for (int i = 1; i <= maxLen; i++)
        powMod[i] = (powMod[i - 1] * BASE) % MOD;
    auto nextHash = [powMod](long long hash, int del, int add, int size)
    {
        hash = (hash - (del * powMod[size]) % MOD + MOD) % MOD;
        hash = (((hash + add) % MOD) * BASE) % MOD;
        return hash;
    };
    map<int, set<int>> lenHashes;
    for (int i = 0; i < removeSize; i++)
    {
        long long hash = 0;
        for (char ch : remove[i])
        {
            hash = (hash + ch - 'a') % MOD;
            hash = (hash * BASE) % MOD;
        }
        lenHashes[remove[i].size()].insert(hash);
    }

    // run: roll hash, remove matches
    int hashStart = 0, onHashes = lenHashes.size();
    int *hashEnd = new int[lenHashes.size()];
    int *currHash = new int[lenHashes.size()];
    for (int i = 0; i < lenHashes.size(); i++)
        hashEnd[i] = currHash[i] = 0;
    int matchEnd = 0;
    while (onHashes != 0)
    {
        int i = -1;
        onHashes = 0;
        for (auto hashes : lenHashes)
        {
            i++;
            if (hashEnd[i] == NA)
                continue;
            onHashes++;
            if (matchEnd != NA)
                currHash[i] = rehash(hashStart, hashEnd[i], hashes.first);
            else
                currHash[i] = nextHash(currHash[i], text[prev[hashStart]] - 'a',
                                       text[hashEnd[i]] - 'a', hashes.first);
        }
        matchEnd = NA;
        i = -1;
        for (auto hashes : lenHashes)
        {
            i++;
            if (matchEnd == NA && hashes.second.find(currHash[i]) != hashes.second.end())
                matchEnd = hashEnd[i];
        }
        if (matchEnd != NA)
            delsstr(hashStart, matchEnd);
        else
            hashStart = next[hashStart];
        for (int iter = 0; iter < lenHashes.size(); iter++)
            hashEnd[iter] = next[hashEnd[iter]];
    }

    // print and delete
    int start;
    for (start = 0; start < text.size(); start++)
        if (prev[start] == NA)
            break;
    for (int iter = start; iter != NA; iter = next[iter])
        cout << text[iter];
    cout << endl;
    delete[] next;
    delete[] prev;
    delete[] hashEnd;
    delete[] currHash;
    return 0;
}