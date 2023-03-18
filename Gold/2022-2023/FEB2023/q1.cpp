// Official:
#pragma GCC optimize("Ofast")
#pragma GCC target("avx2")
#include <iostream>
#include <set>
#include <map>
#include <algorithm>
using namespace std;
using ll = long long;
#define INF 9'223'372'036'854'775'807
#define ps(x) (x < 0 ? 0 : preSum[x])

ll n, a[510], preSum[510];
set<ll> notPartOf;
map<ll, ll> partOf;
multiset<ll> bestMatch;

void remove(int start, int end)
{
    ll value = ps(end) - ps(start - 1);
    bestMatch.erase(bestMatch.find(partOf[value]));
    partOf.erase(value);
    auto first = partOf.begin();
    if (!notPartOf.empty() && value > *notPartOf.begin())
    {
        ll smaller = *prev(notPartOf.upper_bound(value));
        ll halfWay = (value + smaller) / 2 + 1;
        first = partOf.lower_bound(value);
    }
    auto last = partOf.end();
    if (!notPartOf.empty() && value < *prev(notPartOf.end()))
    {
        ll larger = *notPartOf.upper_bound(value);
        ll halfWay = (value + larger - 1) / 2;
        last = partOf.upper_bound(halfWay);
    }
    notPartOf.insert(value);
    for (auto i = first; i != last; i++)
    {
        bestMatch.erase(bestMatch.find(i->second));
        i->second = INF;
        auto it = notPartOf.upper_bound(i->first);
        if (it != notPartOf.end())
            i->second = min(i->second, *it - i->first);
        if (it != notPartOf.begin())
            i->second = min(i->second, i->first - *prev(it));
        bestMatch.insert(i->second);
    }
}

void add(int start, int end)
{
    ll value = ps(end) - ps(start - 1);
    notPartOf.erase(value);
    auto first = partOf.begin();
    if (!notPartOf.empty() && value > *notPartOf.begin())
    {
        ll smaller = *prev(notPartOf.upper_bound(value));
        ll halfWay = (value + smaller) / 2 + 1;
        first = partOf.lower_bound(value);
    }
    auto last = partOf.end();
    if (!notPartOf.empty() && value < *prev(notPartOf.end()))
    {
        ll larger = *notPartOf.upper_bound(value);
        ll halfWay = (value + larger - 1) / 2;
        last = partOf.upper_bound(halfWay);
    }
    for (auto i = first; i != last; i++)
    {
        bestMatch.erase(bestMatch.find(i->second));
        i->second = INF;
        auto it = notPartOf.upper_bound(i->first);
        if (it != notPartOf.end())
            i->second = min(i->second, *it - i->first);
        if (it != notPartOf.begin())
            i->second = min(i->second, i->first - *prev(it));
        bestMatch.insert(i->second);
    }
    ll ans = INF;
    auto it = notPartOf.upper_bound(value);
    if (it != notPartOf.end())
        ans = min(ans, *it - value);
    if (it != notPartOf.begin())
        ans = min(ans, value - *prev(it));
    partOf[value] = ans;
    bestMatch.insert(ans);
}

int main(void)
{
    ios_base::sync_with_stdio(false);
    cin >> n;
    for (int i = 0; i < n; i++)
        cin >> a[i];
    preSum[0] = a[0];
    for (int i = 1; i < n; i++)
        preSum[i] = preSum[i - 1] + a[i];
    for (int i = 0; i < n; i++)
        for (int j = i; j < n; j++)
            notPartOf.insert(ps(j) - ps(i - 1));
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < i; j++)
            remove(j, i - 1);
        for (int j = i; j < n; j++)
            add(i, j);
        cout << *bestMatch.begin() << endl;
    }
    return 0;
}