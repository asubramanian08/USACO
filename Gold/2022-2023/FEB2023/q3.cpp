// Official:
#pragma GCC optimize("Ofast")
#pragma GCC target("avx2")
#include <iostream>
#include <map>
#include <set>
#include <algorithm>
using namespace std;
using pii = pair<int, int>;
#define MOD 1000000007

long long addTop(long long x, int digit)
{
    long long place = 1;
    while (place <= x)
        place *= 10;
    return digit * place + x;
}

int main(void)
{
    ios_base::sync_with_stdio(false);
    long long n, a, b, q, digit[310];
    cin >> n >> a >> b;
    for (int i = 0; i < n; i++)
        cin >> digit[i];
    cin >> q;
    pair<pii, pii> queries[50010];
    for (int i = 0; i < q; i++)
    {
        cin >> queries[i].first.first >> queries[i].first.second;
        queries[i].first.first--;
        queries[i].first.second--;
        queries[i].second.first = i;
    }
    sort(queries, queries + q);
    int currQ = 0;
    for (int i = 0; i < n; i++)
    {
        map<long long, long long> DP;
        set<long long> in;
        DP[0] = 1;
        in.insert(0);
        int j = i;
        long long ans = 0;
        while (currQ < q && queries[currQ].first.first == i)
        {
            for (; j <= queries[currQ].first.second; j++)
            {
                for (auto from : in)
                {
                    if (long long x = from * 10 + digit[j]; x <= b)
                    {
                        DP[x] = (DP[x] + DP[from]) % MOD;
                        if (x >= a)
                            ans = (ans + DP[from]) % MOD;
                    }
                    if (long long x = addTop(from, digit[j]); x <= b)
                    {
                        DP[x] = (DP[x] + DP[from]) % MOD;
                        if (x >= a)
                            ans = (ans + DP[from]) % MOD;
                    }
                }
                for (auto x : DP)
                    in.insert(x.first);
            }
            queries[currQ++].second.second = ans;
        }
    }
    sort(queries, queries + q, [](const pair<pii, pii> &p1, const pair<pii, pii> &p2)
         { return p1.second.first < p2.second.first; });
    for (int i = 0; i < q; i++)
        cout << queries[i].second.second << endl;
    return 0;
}