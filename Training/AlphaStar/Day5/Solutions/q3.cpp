/*Solution  (USACO 2018 December Contest, Gold)

(Analysis by Nick Wu)
Instead of trying to count the number of pairs of cows that are not compatible, we will count the number 
of pairs of cows that are compatible. The answer is therefore (𝑁(𝑁−1))/2 minus the number of pairs of 
cows that are compatible.

The most direct approach of checking every pair of cows for compatibility takes 𝑂(𝑁^2) and will be too 
slow.

The most naive 𝑂(𝑁^2) solution will loop over all pairs of cows and look for a common flavor. This 
solution with no optimizations is unlikely to pass any additional test cases. One way to optimize the 
𝑂(𝑁^2) solution is to, for a given ice cream flavor, keep track of every cow that likes that flavor, and 
to then only loop over pairs of cows if they are known to share a common flavor. If the cows' favorite ice 
cream flavors are generated uniformly at random, this solution performs really well, since any given 
flavor, for the given bounds, will be liked by 0.25 cows in expectation.

Fortunately, this optimized 𝑂(𝑁^2) solution does not pass all of the test cases. However, it does motivate 
us towards the intended solution, which is linear in 𝑁.

Imagine for simplicity that the only flavors that are a favorite of at least 2 cows are flavor 1 and flavor
2. If we only count the number of pairs of cows that like flavor 1 and the number of pairs of cows that 
like flavor 2, this is an overestimate of the number of pairs of cows that are compatible because we have 
double-counted by the number of pairs of cows that like both flavor 1 and flavor 2.

This motivates the following inclusion-exclusion solution: for every subset of flavors, count how many 
pairs of cows that like all flavors within each subset. We add all the counts for subsets of size 1, then 
to avoid double-counting, we subtract all the counts for subsets of size 2. We then add all the counts of 
subsets of size 3, subtract all the counts of subsets of size 4, and add the counts of subsets of size 5.

There are too many subsets of size 2 and more to iterate over directly, so we can explicitly generate all 
the subsets of flavors where at least one cow likes all the flavors in that subset. There are at most 31𝑁 
distinct such subsets.

Below is Brian Dean's code. */

#include <iostream>
#include <fstream>
#include <map>
#include <algorithm>
using namespace std;

long long N, inc_exc[] = {-1, +1, -1, +1, -1, +1};

// a set of up to 5 ints
struct S5
{
    int n;
    int v[5]; // zero-pad if not used
};

S5 A[100000];

bool operator<(const S5 &a, const S5 &b)
{
    for (int j = 0; j < 5; j++)
    {
        if (a.v[j] < b.v[j])
            return true;
        if (a.v[j] > b.v[j])
            return false;
    }
    return false;
}

S5 get_subset(S5 &a, int x)
{
    S5 result = {0, {0, 0, 0, 0, 0}};
    for (int j = 0; j < 5; j++)
        if ((1 << j) & x)
            result.v[result.n++] = a.v[j];
    return result;
}

map<S5, int> subsets;

int main(void)
{
    ifstream fin("cowpatibility.in");
    fin >> N;
    for (int i = 0; i < N; i++)
    {
        A[i].n = 5;
        for (int j = 0; j < 5; j++)
            fin >> A[i].v[j];
        sort(A[i].v, A[i].v + 5);
        for (int x = 1; x < 32; x++)
            subsets[get_subset(A[i], x)]++;
    }

    long long answer = N * (N - 1) / 2;
    for (auto &p : subsets)
        answer -= inc_exc[p.first.n] * p.second * (p.second - 1) / 2;

    ofstream fout("cowpatibility.out");
    fout << answer << "\n";
    return 0;
}
// (Reference : Retrieved from USACO website)