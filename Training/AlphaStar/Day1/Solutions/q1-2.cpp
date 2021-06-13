/* A different approach is to, again, add each statement one-at-a-time, but do not repeat the entire 
flood-fill each time. Keep track of the components as you go. Every time you add an edge, there are two 
cases: if its endpoints are in the same components, we just have to check that the edge is consistent with 
the given partition of that component into A and B. If the endpoints are in separate components, we have 
to merge the two components together: this takes O(N) time. Since there are at most N merges to be done, 
this algorithm is O(M + N2).

Here is a C++ solution which implements the O(N2) solution: */

#include <cstdio>
#include <cstring>
#define NMAX 1005

// For any positive C, cows labelled C or -C are in the same component.
// Either C's are truth tellers and -C's are liars, or other way around.
int components[NMAX];
int main()
{
    freopen("truth.in", "r", stdin);
    freopen("truth.out", "w", stdout);
    int n, m;
    scanf("%d", &n);
    scanf("%d", &m);
    for (int i = 0; i < n; i++)
    {
        components[i] = i + 1;
    }
    for (int line = 0; line < m; line++)
    {
        int a, b;
        char c;
        scanf("%d", &a);
        scanf("%d", &b);
        a--;
        b--;
        do
        {
            c = fgetc(stdin);
        } while (c != 'L' && c != 'T');
        if (components[a] == components[b] || components[a] == -components[b])
        {

            // If a and b are in the same component, check that the newly added
            // edge is consistent.
            if ((components[a] == components[b]) ^ (c == 'T'))
            {
                printf("%d\n", line);
                return 0;
            }
        }
        else
        {
            // If a and bare in different components, merge the two components
            // By finding everything in b's component and moving it to a's
            // component.

            int acomp = (c == 'T' ? components[a] : -components[a]);
            int bcomp = components[b];
            for (int i = 0; i < n; i++)
            {
                if (components[i] == bcomp)
                {
                    components[i] = acomp;
                }
                else if (components[i] == -bcomp)
                {
                    components[i] = -acomp;
                }
            }
        }
    }
    printf("%d\n", m);
    return 0;
}