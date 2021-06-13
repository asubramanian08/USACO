/* USACO MAR08 Problem 'river' Analysis by Alex Schwendner

First note that since all cows are equivalent we can entirely describe an intermediate state of this process by 
how many cows are on each side of the river and by the side of the river that FJ is on. Second, the variables of 
the number of cows on the near and far sides of the river aren't really distinct variables, since they must 
always add up to N. Lastly, note that since adding another cow to the raft always makes the raft slower, FJ will 
never want to take a cow from the far bank back to the near bank: cows only cross the river in one direction.

We describe an intermediate state by the number of cows remaining to be transported. Construct a size N array 
where the i-th entry is the time to transport a total of i cows starting at the near bank. Let this value be 
f(i). At each step before the last, FJ will make a round trip and transport some of the cows to the far bank. At 
the last step, FJ goes one-way with all the remaining cows.

At a step where i cows remain on the near bank, FJ can transport 1,2,3,...,i cows on his next trip. This gives us 
the relation:

f(i) = min(2*M+M_1+f(i-1), 2*M+M_1+M_2+f(i-2), 2*M+M_1+M_2+M_3+f(i-3), ..., 2*M+M_1+...+M_{i- 1}+f(1), 
M+M_1+...+M_i+0)

We use this to evaluate f(i) and store it in our array given the values of f(1) through f(i-1). The time to 
evaluate one value is O(N), and there are N values to evaluate. This yields O(N^2) time. With N=2,500, this will 
be fine.

Code: */

#include <stdio.h>
const int MAXN = 5000;
int n;
int m[MAXN];
int cost[MAXN];
int main()
{
    FILE *fin = fopen("river.in", "r");
    fscanf(fin, "%d %d", &n, &m[0]);
    for (int i = 1; i <= n; ++i)
    {
        int dm;
        fscanf(fin, "%d", &dm);
        m[i] = m[i - 1] + dm;
    }
    fclose(fin);
    cost[0] = -m[0];
    for (int i = 1; i <= n; ++i)
    {
        cost[i] = m[i];
        for (int j = 0; j <= i; ++j)
        {
            //cost[i] < ? = m[j] + m[0] + cost[i - j]; //changed to if statement below
            if (cost[i] < m[j] + m[0] + cost[i - j])
                cost[i] = m[j] + m[0] + cost[i - j];
        }
    }
    FILE *fout = fopen("river.out", "w");
    fprintf(fout, "%d\n", cost[n]);
    fclose(fout);
}