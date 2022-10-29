// Some comment
#pragma GCC optimize("Ofast")
#pragma GCC target("avx2")
#include <iostream>
using namespace std;

int main(void)
{
    // IO Set up
    ios_base::sync_with_stdio(false);
    // cin.tie(nullptr); // not useful
#ifndef HOME
    freopen("file.in", "r", stdin);
    freopen("file.out", "w", stdout);
#endif

    return 0;
}