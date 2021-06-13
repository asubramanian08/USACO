/*Solution USACO 2019 US Open Contest, Gold (Analysis by Dhruv Rohatgi )
To understand how many swaps are needed to balance the number of inversions in each subarray, we first need to 
understand how a swap changes the number of inversions in each subarray. In particular, we're interested in the 
quantity Δ=# inversions in first half−# inversions in second half

Call a swap between the 𝑛-th and (𝑛+1)-st elements of the array a "central" swap. Any non-central swap either 
increases or decreases Δ by 1. Furthermore, a central swap of the form 1,0→0,1 increases Δ by a fixed amount: 
# ones in array−𝑛   . And a central swap of the form 0,1→1,0 decreases Δ by the same amount.

Suppose that we use no central swaps. Then we need to perform at least |Δ| swaps. It turns out that this is 
sufficient: in the subarray with more inversions, we can always perform swaps to decrease the number of 
inversions.

Notice that any sequence of swaps can be interpreted as moving around the 1s in the array. Any optimal sequence 
never swaps two 1s, and the path traced out by each 1 is monotonic. So if the sequence increases the number of 
1s in the first half by t(some integer, possibly negative), then it's optimal to perform |𝑡| central swaps (all 
of them moving 1s in the same direction).

So let's try 𝑡=0,1,2,… in order (the cases 𝑡<0 are similar). As 𝑡 increases, we push more and more 1s from the 
first half of the subarray to the second half. Each push has three components:

1) non-central swaps in the first half, to move the 1 to position 𝑛
2) non-central swaps in the second half, to make sure that there's a 0 at position 𝑛+1
3) a single central swap moving the 1 from position 𝑛 to the now-empty position 𝑛+1 Note that for a fixed 𝑡, these 
swaps are all necessary: we moved each 1 as little as possible while still having 𝑡 central swaps.

We need to track Δ through each push. We use a two-pointers approach: one pointer in the first half of the array, 
pointing to the rightmost 1. And one pointer in the second half of the array, pointing to the leftmost 0. These 
pointers allow us to easily compute the number of non-central swaps forced by the push, and thus the change in Δ. 
As we've shown above, the effect of the central swap is also straightforward.

Finally, suppose we know the value of Δ after 𝑡 central swaps (and the associated pushes). Then as in the 𝑡=0 
case, we need |Δ| more non-central swaps to balance the number of inversions (this is in addition to the "forced" 
swaps). As 𝑡 increases, we simply track the best number of swaps found so far.

Since each pointer is monotonic, the overall time complexity is 𝑂(𝑛)

This solution implements the above idea. It handles the 𝑡<0 cases by viewing the sequence of swaps as moving the 
0s rather than moving the 1s. This allows the above 𝑡≥0 logic to be reused. */

#include <iostream>
#include <algorithm>
using namespace std;
#define MAXN 100000

int N;
int A[2 * MAXN];
long long best;
int ones;

long long llabs(long long x)
{
    if (x < 0)
        return -x;
    return x;
}

long long countInversions(int a, int b)
{
    long long t = 0;
    int n1 = 0;
    for (int i = a; i <= b; i++)
    {
        if (A[i] == 1)
            n1++;
        else
            t += n1;
    }
    return t;
}

int tp, sgn;

void solve()
{
    long long inv0 = countInversions(0, N - 1);
    long long inv1 = countInversions(N, 2 * N - 1);
    long long dif = inv0 - inv1;
    best = min(best, llabs(dif));
    int n1 = 0;
    int j = N;
    int displaced = 0;
    long long cost = 0;
    for (int i = N - 1; i >= 0; i--)
        if (A[i] == tp)
        {
            dif -= sgn * (N - 1 - i), cost += N - 1 - i;
            dif += sgn * (ones - N), cost++;
            dif += sgn * n1, cost += n1;
            dif += sgn * displaced, cost += displaced;
            n1++;
            if (n1 + displaced > N)
                return;
            while (n1 + displaced > j - N)
            {
                if (A[j] == 1 - tp)
                    j++;
                else if (j == 2 * N - 1)
                    return;
                else
                {
                    dif += sgn * (N + n1 + displaced - j), cost += N + n1 + displaced - j;
                    displaced++;
                    j++;
                }
            }
            best = min(best, cost + llabs(dif));
        }
}

int main()
{
    cin >> N;
    for (int i = 0; i < 2 * N; i++)
    {
        cin >> A[i];
        ones += A[i];
    }
    best = MAXN * ((long long)MAXN);
    tp = 1, sgn = 1;
    solve();
    tp = 0, sgn = -1;
    solve();
    cout << best << '\n';
}
//(Reference : Retrieved from USACO website)