/*USACO JAN16 Problem 'radio' Analysis by Mark Gordon

This problem is actually a veiled Dynamic Time Warping problem where the error function is the squared 
distance between FJ and Bessie.

Therefore the problem can be solved with dynamic programming. For each possible position of Farmer John 
and Bessie we can compute the minimum energy required for them to both get to their end position by trying 
to step FJ forward, step Bessie forward, our move them both forward.

Here's my code implementing this solution.*/

#include <iostream>
#include <vector>
#include <cstring>
#include <cstdio>
#include <map>
using namespace std;
#define INF 0x7FFFFFFFFFFFFFFFLL
long long memo[1010][1010];
vector<pair<long long, long long>> F;
vector<pair<long long, long long>> B;
long long solve(int fi, int bi)
{
    /* The energy cost of the radio for this timestep. */
    long long base = (F[fi].first - B[bi].first) * (F[fi].first - B[bi].first) +
                     (F[fi].second - B[bi].second) * (F[fi].second - B[bi].second);
    if (fi + 1 == F.size() && bi + 1 == B.size())
    {
        return base;
    }
    long long &ref = memo[fi][bi];
    if (ref != -1)
        return ref;
    /* Don't include the cost of the first timestep. */
    if (fi == 0 && bi == 0)
        base = 0;
    ref = INF;
    if (fi + 1 < F.size())
    {
        /* Step FJ forward. */
        ref = min(ref, base + solve(fi + 1, bi));
    }
    if (bi + 1 < B.size())
    {
        /* Step Bessie forward. */
        ref = min(ref, base + solve(fi, bi + 1));
    }
    if (fi + 1 < F.size() && bi + 1 < B.size())
    {
        /* Step both forward. */
        ref = min(ref, base + solve(fi + 1, bi + 1));
    }
    return ref;
}
int main()
{
    freopen("radio.in", "r", stdin);
    freopen("radio.out", "w", stdout);

    map<char, int> dx, dy;
    dx['E'] = 1;
    dx['W'] = -1;
    dy['N'] = 1;
    dy['S'] = -1;

    int N, M;
    cin >> N >> M;
    int fx, fy, bx, by;
    cin >> fx >> fy >> bx >> by;
    string SF, SB;
    cin >> SF >> SB;

    /* Compute FJ's path. */
    F.push_back(make_pair(fx, fy));
    for (int i = 0; i < SF.size(); i++)
    {
        fx += dx[SF[i]];
        fy += dy[SF[i]];
        F.push_back(make_pair(fx, fy));
    }

    /* Compute Bessie's path. */
    B.push_back(make_pair(bx, by));
    for (int i = 0; i < SB.size(); i++)
    {
        bx += dx[SB[i]];
        by += dy[SB[i]];
        B.push_back(make_pair(bx, by));
    }
    memset(memo, -1, sizeof(memo));
    cout << solve(0, 0) << endl;
    return 0;
}