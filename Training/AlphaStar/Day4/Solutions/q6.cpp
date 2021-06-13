/*USACO FEB14 Problem 'scode' Analysis by Brian Dean

This problem is solved with dynamic programming, or equivalently, using recursion but with "memoization" 
(remembering solutions of smaller subproblems once they are solved). Essentially, we count the number of 
ways to obtain each string S by building it from smaller strings S' (using recursion to count the number 
of ways to get each S'). However, once we have computed the number of ways to obtain a substring, we 
record this answer in a table so that in the future, if we end up with the same subproblem, we can just 
report the answer from the table instead of launching an expensive recursive calculation.

Richard Peng's code is below -- he is quite fond of using functions called "moo" as you can see...*/

#include <cstdio>
#include <cstring>
#include <string>
#include <iostream>
#include <map>
using namespace std;
const int M = 2014;
map<string, int> lookup;
int moo(string s)
{
    if (lookup.find(s) != lookup.end())
    {
        return lookup[s];
    }
    int ans = 1;
    int l = s.length();
    for (int i = 1; i * 2 < l; ++i)
    {
        if (s.substr(0, i) == s.substr(l - i, i))
        {
            ans += moo(s.substr(i, l - i));
        }
        if (s.substr(0, i) == s.substr(i, i))
        {
            ans += moo(s.substr(i, l - i));
        }
        if (s.substr(0, i) == s.substr(l - i, i))
        {
            ans += moo(s.substr(0, l - i));
        }
        if (s.substr(l - i * 2, i) == s.substr(l - i, i))
        {
            ans += moo(s.substr(0, l - i));
        }
    }
    ans %= M;
    lookup[s] = ans;
    return ans;
}
int main()
{
    freopen("scode.in", "r", stdin);
    freopen("scode.out", "w", stdout);
    lookup.clear();
    string s;
    cin >> s;
    int ans = (moo(s) + M - 1) % M;
    cout << ans << endl;
    return 0;
}