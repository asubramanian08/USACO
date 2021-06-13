/*Solution(USACO 2018 US Open Contest, Gold)

We can solve this problem by binary searching on the answer. How can we tell if a given ratio x is 
achievable? What we want is a set S of cows satisfying,

( ∑𝑖∈𝑆 (𝑇𝑖) / ∑𝑖∈𝑆 (𝑊𝑖)) ≥ 𝑥 and ∑𝑖∈𝑆 (𝑊𝑖) ≥ 𝑤.

The first condition is more easily expressed as

∑𝑖∈𝑆 (𝑇𝑖−𝑥𝑊𝑖) ≥ 0.

Binary searching with real numbers can be tricky, but here, our life is simplified because we know we are
only looking for ⌊1000𝑥⌋. We can let y = 1000x and then we want to find the maximum integer y such that

∑𝑖∈𝑆 (1000𝑇𝑖−𝑦𝑊𝑖) ≥ 0

is satisfiable for some S. Let's call the quantity 1000𝑇𝑖 − 𝑦𝑊𝑖 the adjusted-talent-score.

To do this, we can use a simple knapsack DP, where we compute, for each j and k, the maximum adjusted - 
talent - score achievable with a subset of the first j cows and exactly k weight.The maximum total weight 
is very high, but we can take a shortcut since we do not care about weights higher than w - or at least, 
for a given set of cows with weight at least w, we don't care what its exact weight is. The DP, then, is 
𝑂(𝑤𝑛). The total runtime would be 𝑂(𝑤𝑛log(𝑡)) where t is the maximum value of y.*/

#include <cstdio>
#include <algorithm>
#include <cassert>
using namespace std;

#define NMAX 250
#define WMAX 1000

#define infinite 1000000000000000000LL

// The inputs
int weights[NMAX];
int talent[NMAX];

int n;
int w;

// The dp state.
// For 0 <= i < w, this is the maximum adjusted-talent-score achievable
// with weight exactly i.
// For i=w, this is the maximum talent achievable
// with weight AT LEAST w.
long long dp[WMAX + 1];

// Check if a ratio of y/1000 is achievable.
bool doable(int y)
{
    for (int i = 0; i <= w; i++)
    {
        dp[i] = -infinite;
    }
    dp[0] = 0;

    for (int j = 0; j < n; j++)
    {
        long long value = 1000 * (long long)talent[j] - y * (long long)weights[j];
        int inc = weights[j];
        for (int k = w; k >= 0; k--)
        {
            int k1 = min(w, k + inc);
            if (dp[k] != -infinite)
            {
                if (dp[k1] < dp[k] + value)
                {
                    dp[k1] = dp[k] + value;
                }
            }
        }
    }

    return dp[w] >= 0;
}

int main()
{
    scanf("%d", &n);
    scanf("%d", &w);
    assert(1 <= n && n <= NMAX);
    assert(1 <= w && w <= WMAX);

    for (int i = 0; i < n; i++)
    {
        scanf("%d", &weights[i]);
        scanf("%d", &talent[i]);
        assert(1 <= weights[i] && weights[i] <= 1000000);
        assert(1 <= talent[i] && talent[i] <= 1000);
    }

    // Binary search
    // Invariant: lo <= answer < hi
    int lo = 0;
    int hi = (1000 * 250 * 1000) + 1;
    while (hi > lo + 1)
    {
        int mid = (lo + hi) / 2;
        if (doable(mid))
        {
            lo = mid;
        }
        else
        {
            hi = mid;
        }
    }
    printf("%d\n", lo);
}

//(Reference : Retrieved from USACO website)