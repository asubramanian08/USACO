/*
USACO DEC13 Problem 'shuffle' Analysis by Mark Gordon

This problem can be converted something a bit easier to understand; Given an array of N elements 
initialized form 1 to N we need to apply the Bessie shuffle to the elements in the range [1, M], [2, M+1],
..., [N-M+1,N]. We can see that if we then reverse the permutation we get the final state of shuffled deck.

The naive algorithm of applying the Bessie shuffle (N-M+1) times will take too long. Each Bessie shuffle
will take O(M) time which gives the overall O((N-M)M) running time.

To fix this observe that we can shift each element of the permutation one to the left (and the first 
element going to the end) after each application of the Bessie shuffle. Viewing it this way, we always 
apply the Bessie shuffle to the first M elements and then shift the whole permutation left. These two 
steps can be viewed as permutations on N elements, and the effect of them taken together (their 
composition) is also a permutation.

This means we can calculate a single permutation which we need to apply (N-M+1) times to 1..N. To do this 
we can use repeated squaring, thus solving the problem in O(N log(N - M)) time. Of course, we need to 
cancel those N-M+1 left shifts with an N-M+1 right shift.

Below is my code to solve this problem. See the gold analysis for a faster solution applicable when N is 
very large.*/

#include <iostream>
#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;
#define MAXN 100010
int X[MAXN];
int Y[MAXN];
int PI[MAXN];
void compose(int *R, int *A, int *B, int N)
{
    for (int i = 0; i < N; i++)
    {
        R[i] = A[B[i]];
    }
}
int main()
{
    freopen("shuffle.in", "r", stdin);
    freopen("shuffle.out", "w", stdout);
    int N, M, Q;
    cin >> N >> M >> Q;
    int T = N - M + 1;
    for (int i = 0; i < N; i++)
    {
        X[i] = i;
        if (i < M)
        {
            int x;
            cin >> x;
            x--;
            PI[x] = i;
        }
        else
        {
            PI[i] = i;
        }
    }
    rotate(PI, PI + 1, PI + N);
    for (int i = 31 - __builtin_clz(T); i >= 0; i--)
    {
        compose(Y, X, X, N);
        memcpy(X, Y, sizeof(X));
        if (T & 1 << i)
        {
            compose(Y, X, PI, N);
            memcpy(X, Y, sizeof(X));
        }
    }
    for (int i = 0; i < Q; i++)
    {
        int x;
        cin >> x;
        cout << X[(N + M - 1 - x) % N] + 1 << '\n';
    }
    return 0;
}