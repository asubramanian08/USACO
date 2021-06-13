/* There is also a divide-and-conquer approach: pick the first 6 cows and the last six cows, brute force 
both halves in 6! time, and then compute the # of edges that cross between the halves. Charge the wire to 
get to the half-way mark as part of the cost of each half, so that the two problems are independent. This 
approach is (12 choose 6)*6! = 665,000 operations, well within the time limit.

C++ divide and conquer: */
#include <iostream>
using namespace std;

int N;
int E[12][3];
int A[12];
int B[12];
int C[1 << 12];
int D[1 << 12];
bool cn[12][12];
int main()
{
    freopen("haywire.in", "r", stdin);
    freopen("haywire.out", "w", stdout);
    cin >> N;
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            cin >> E[i][j];
            E[i][j]--;
            cn[i][E[i][j]] = true;
        }
    }
    memset(C, 0, sizeof(C));
    memset(D, 0x1F, sizeof(D));
    for (int i = 0; i < 1 << N; i++)
    {
        int M = 0;
        for (int j = 0; j < N; j++)
        {
            if (i & 1 << j)
            {
                A[M++] = j;
                for (int k = 0; k < 3; k++)
                {
                    if (~i & 1 << E[j][k])
                    {
                        C[i]++;
                    }
                }
            }
        }
        if (M > N / 2)
            continue;
        int &r = D[i];
        memset(B, 0, sizeof(B));
        do
        {
            for (int j = 0; j < M; j++)
            {
                B[A[j]] = j;
            }
            int s = 0;
            for (int j = 0; j < M; j++)
            {
                for (int k = 0; k < 3; k++)
                {
                    s += max(0, j - B[E[A[j]][k]]);
                }
            }
            r = min(r, s);
        } while (next_permutation(A, A + M));
    }
    int res = 0x7FFFFFFF;
    for (int i = 0; i < 1 << N; i++)
    {
        res = min(res, D[i] + D[~i & (1 << N) - 1] + C[i]);
    }
    cout << res << endl;
    return 0;
}