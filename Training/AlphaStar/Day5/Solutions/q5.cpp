/*USACO OPEN12 Problem 'bookshelf' Analysis by Mark Gordon

Suppose we decide that we want to place k books on the last bookshelf (and we've already checked that they 
can fit on one shelf). Then the height of the bookshelves is max(H[n-k+1], H[n-k+2], ..., H[n]) plus the 
cost of constructing shelves for the initial n-k books. This screams dynamic programming!

Let C(x) to be the minimum height of the bookshelves after placing the first x books (and let C(0) = 0). 
Then the initial observation allows us to construct the recurrence C(x) = min({C(y) + max(H[y+1], H[y+2],
..., H[x]) : 0 <= y < x and sum(W[y+1], W[y+2], ..., W[x]) <= L})

This immediately lends itself to an O(N^3) solution. By computing the max and sum terms as we iterate over 
y we can actually reduce the solution down to O(N^2) to look something like:

C(x) = 0
for i = 1 to N
    hmax = 0
    for j = i-1 to 0 step -1
    wsum = wsum + W[j+1] hmax = max(hmax, H[j+1]) 
    if wsum <= L
        C(x) = min(C(x), hmax + C(j))

However, for the gold version of the problem this is not enough. We'll use the same basic structure for 
the new solution but we'll be able to bring the runtime down to O(N log N) using two observations.

First, we can maintain which sections of the array correspond to different hmax terms (hmax from the 
solution above) efficiently as we iterate over the books. When we move past book i the set of positions 
with hmax H[i] is exactly those with hmax no larger than H[i] when we were at i- 1. As hmax is 
non-increasing with j we can simply keep a list of the intervals of books with the same hmax and update 
the list by merging the intervals with hmax <= H[i] into our newly created interval. Because two indicies 
can never be 'unmerged' it follows that we can do at most N-1 merge operations over the course of the 
algorithm. We also must take care to erase indicies from the first interval if the wsum term gets too 
large.

The second observation is that C(x) is non-decreasing. That is, we can't get bookshelves of smaller height 
by adding more books. This means that we should only consider books that begin an interval formed in the 
previous step. Therefore each time we alter the set of intervals we erase any old costs of initial 
elements from a sorted set and insert any new costs. Then C(x) is simply the smallest element in this set. 

Below is my solution to this problem.*/

#include <iostream>
#include <set>
#define MAXN 2005
using namespace std;

int W[MAXN];
int H[MAXN];
long long DP[MAXN];
int SA[MAXN];
int main()
{
    int N, L;
    cin >> N >> L;
    int *S = SA;
    int rsz = 0;
    int wsum = DP[0] = 0;
    multiset<long long> bst;
    for (int i = 1, j = 1; i <= N; i++)
    {
        cin >> H[i] >> W[i];
        for (S[rsz++] = 1; rsz > 1 && H[i - S[rsz - 1]] <= H[i]; rsz--)
        {
            bst.erase(bst.find(H[i - S[rsz - 1]] + DP[i - S[rsz - 1] - S[rsz - 2]]));
            S[rsz - 2] += S[rsz - 1];
        }
        bst.insert(H[i] + DP[i - S[rsz - 1]]);
        wsum += W[i];
        for (; wsum > L; j++)
        {
            wsum -= W[j];
            bst.erase(bst.find(H[j + S[0] - 1] + DP[j - 1]));
            if (--S[0] == 0)
            {
                ++S;
                rsz--;
            }
            else
            {
                bst.insert(H[j + S[0]] + DP[j]);
            }
        }
        DP[i] = *bst.begin();
    }
    cout << DP[N] << endl;
}