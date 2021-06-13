/*Solution  (USACO 2019 February Contest, Gold)

(Analysis by Nick Wu)
We'll assume familiarity with the silver division problem in this solution. We start by computing a 2D 
prefix sum so we can get the exact count of coats of paint for each location on the roof, and we can also 
compute at this time the area of the rectangle covered by exactly 𝐾 coats of paint.

We'll start by solving the simpler problem where we apply at most one additional coat of paint. There are 
𝑂(200^4) possible coats of paint that we can apply, so even if we somehow figured out the area covered by
exactly 𝐾 coats in constant time, this approach would still time out. We'll start by thinking about the 
one-dimensional variant of the problem. The only components of the rectangle that matter are components 
with exactly 𝐾 coats of paint on them, and components with exactly 𝐾−1 coats of paint on them. If we cover
the former with a coat of paint, then the area decreases by one. If we cover the latter with a coat of 
paint, then the area increases by one. For any other number of coats of paint, the area does not change. 
We can take the number of coats of paint and then convert it to an array of integers where each integer is
between −1 and 1, and then we wish to find the subarray of maximum sum. This is a problem that we can 
solve in linear time! We can scan the array from left to right, keeping a running track of the sum that we
have accumulated so far. The moment the running sum goes below zero, we know that that the given prefix 
can be excluded so we can reset the leftmost point of the subarray. Finally, note that there are a 
quadratic number of subarrays that could be considered.

From the above, we've reduced the number of entries that we consider by a linear factor. Note that it is
theoretically possible to make 𝑂(200^3) fit in time. To apply this technique to the two-dimension variant,
we'll fix the 𝑥-coordinates of the rectangle where we apply the coat of paint. We can sweep over the 
𝑦-coordinates going from 0 to 200 and apply the same technique of maintaining a running sum and keeping 
track of the maximum value it has, resetting it to zero if it ever becomes negative. There are 𝑂(200^2)
different pairs of 𝑥-coordinates to consider, and if we have a prefix sum array, we can sweep over all 
coordinates in 𝑂(200), for 𝑂(200^3).

How does this help us solve the case where two disjoint rectangles can be coated with paint? For any 
arrangement of two disjoint rectangles, there exists either a horizontal line or a vertical line such that
the rectangles do not lie on the same side of the line.

For each of the 𝑂(200^3) rectangles that we consider in the one-rectangle scenario, we can also cache the
four lines that touch the borders of those rectangles, and which side of the line that rectangle lies on. 
We can then consider every horizontal and vertical line and combine the two best rectangles on either side,
and save the best result.*/

#include <bits/stdc++.h>

using namespace std;

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<pii, int> ppiii;

int dp[201][201];
int actual[201][201];

int rectangleSum(int a, int b, int x, int y)
{
    return actual[a + x][b + y] - actual[a][b + y] - actual[a + x][b] + actual[a][b];
}

int topDP[201];
int bottomDP[201];
int leftDP[201];
int rightDP[201];

int main()
{
    freopen("paintbarn.in", "r", stdin);
    freopen("paintbarn.out", "w", stdout);
    int n, k;
    cin >> n >> k;
    while (n--)
    {
        int a, b, c, d;
        cin >> a >> b >> c >> d;
        dp[a][b]++;
        dp[a][d]--;
        dp[c][b]--;
        dp[c][d]++;
    }
    int currAmt = 0;
    int ret = 0;
    for (int i = 0; i < 200; i++)
    {
        for (int j = 0; j < 200; j++)
        {
            if (i)
                dp[i][j] += dp[i - 1][j];
            if (j)
                dp[i][j] += dp[i][j - 1];
            if (i && j)
                dp[i][j] -= dp[i - 1][j - 1];
            if (dp[i][j] == k - 1)
                actual[i + 1][j + 1] = 1;
            if (dp[i][j] == k)
            {
                currAmt++;
                actual[i + 1][j + 1] = -1;
            }
        }
    }
    for (int i = 1; i <= 200; i++)
    {
        for (int j = 1; j <= 200; j++)
        {
            actual[i][j] += actual[i - 1][j];
            actual[i][j] += actual[i][j - 1];
            actual[i][j] -= actual[i - 1][j - 1];
        }
    }
    for (int lhs = 0; lhs <= 200; lhs++)
    {
        for (int len = 1; lhs + len <= 200; len++)
        {
            int topSum = 0;
            int leftSum = 0;
            int rightSum = 0;
            int bottomSum = 0;
            for (int i = 1; i <= 200; i++)
            {
                ret = max(ret, topDP[i] = max(topDP[i], topSum = max(0, topSum + rectangleSum(i - 1, lhs, 1, len))));
                ret = max(ret, leftDP[i] = max(leftDP[i], leftSum = max(0, leftSum + rectangleSum(lhs, i - 1, len, 1))));
                ret = max(ret, rightDP[i] = max(rightDP[i], rightSum = max(0, rightSum + rectangleSum(lhs, 200 - i, len, 1))));
                ret = max(ret, bottomDP[i] = max(bottomDP[i], bottomSum = max(0, bottomSum + rectangleSum(200 - i, lhs, 1, len))));
            }
        }
    }
    for (int i = 2; i <= 200; i++)
    {
        topDP[i] = max(topDP[i], topDP[i - 1]);
        leftDP[i] = max(leftDP[i], leftDP[i - 1]);
        rightDP[i] = max(rightDP[i], rightDP[i - 1]);
        bottomDP[i] = max(bottomDP[i], bottomDP[i - 1]);
    }
    for (int i = 1; i <= 199; i++)
    {
        ret = max(ret, topDP[i] + bottomDP[200 - i]);
        ret = max(ret, leftDP[i] + rightDP[200 - i]);
    }
    cout << ret + currAmt << "\n";
}
//(Reference : Retrieved from USACO website)