/* USACO NOV07 Problem 'bcl' Analysis by Christos Tzamos

This problem can be solved with dynamic programming on the intervals of cows but there is also a simple greedy 
strategy.

Between the two cows in the edges, you must always pick the cow with the smallest initial letter. If both cows 
have the same initial letter in order to decide you must look a little bit deeper and check the second cows in 
the line's edges or the third ones if those are equal and so on until you find two cows that are different. Then 
you pick the cow from the side of the smallest one.

This process can be summarized as follows. At any given interval [a,b] with string S([a,b]) you choose:

Cow a if S([a,b]) < rev( S([a,b]) )
Cow b otherwise
where rev(S) is the reverse string e.g. rev("abc") = "cba"

This can be implemented in O(N^2) but we can achieve O(NlogN) by using suffix arrays.
Here are the two implementations:
The O(N^2): */

#include <cstdio>
char S[2010], ln = 0;
void prnt(char a)
{
    if (ln == 80)
    {
        printf("\n");
        ln = 0;
    }
    printf("%c", a);
    ln++;
}
int main()
{
    int i, j, N, pi, pj, val;

    freopen("bcl.in", "r", stdin);
    freopen("bcl.out", "w", stdout);
    scanf("%d", &N);
    for (i = 0; i < N; i++)
        scanf(" %c ", S + i);
    i = 0, j = N - 1;
    while (i <= j)
    {
        if (S[i] < S[j])
        {
            prnt(S[i]);
            i++;
        }
        else if (S[i] > S[j])
        {
            prnt(S[j]);
            j--;
        }
        else
        {
            pi = i + 1;
            pj = j - 1;
            val = S[i];
            while (pj - pi > 1 && S[pi] == S[pj])
            {
                pi++, pj--;
            }
            if (S[pi] < S[pj])
                prnt(S[i]), i++;
            else
                prnt(S[j]), j--;
        }
    }
    printf("\n");
}