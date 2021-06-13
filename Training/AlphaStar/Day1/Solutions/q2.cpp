/*USACO OPEN09 Problem 'cdgame' Analysis by Neal Wu
Call a number a winning number if Bessie will win by starting with this number, and a losing number 
otherwise. First of all, 0 is a losing number. Now, given a number, how can we determine if it is a 
winning number or a losing number?
The answer is fairly simple: a number is a winning number if any number that can be reached from it is a 
losing number. (Thus, you can make a move that reaches this number and forces your opponent to lose.) The 
number is a losing number if every number that can be reached from it is a winning number. (Thus, no 
matter what move you make, your opponent can win.)
We can precompute, for each number in our range (in increasing order) whether the number is a winning or 
losing number and then output our results. For each number, we need to find the largest and smallest 
digits of the number. We then try to subtract these from our number and see if either of the numbers 
produced is a losing number. The simplest way to do this is to extract all the digits using mod operators,
though one must be careful to avoid using the digit 0. This idea is shown in the solution below: */
#include <cstdio>
#include <algorithm>
using namespace std;
FILE *in = fopen("cdgame.in", "r"), *out = fopen("cdgame.out", "w");
const int MAXN = 1000005;
int G, N;
bool win[MAXN];
void solve()
{
    win[0] = false;
    for (int i = 1; i < MAXN; i++)
    {
        int mind = 10, maxd = 0;
        for (int t = i; t > 0; t /= 10)
            if (t % 10 != 0)
            {
                mind = min(mind, t % 10);
                maxd = max(maxd, t % 10);
            }
        win[i] = !win[i - mind] || !win[i - maxd];
    }
}
int main()
{
    solve();
    for (fscanf(in, "%d", &G); G > 0; G--)
    {
        fscanf(in, "%d", &N);
        fputs(win[N] ? "YES\n" : "NO\n", out);
    }
    return 0;
}