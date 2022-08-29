// Start: 8:25
// Think: 8:31
// Write: 8:34
// Debug: 8:41
#include <iostream>
using namespace std;

int main(void)
{
    //read
#ifndef HOME
    freopen("poker.in", "r", stdin);
    freopen("poker.out", "w", stdout);
#endif
    int ranks;
    cin >> ranks;
    int *cards = new int[ranks];
    for (int i = 0; i < ranks; i++)
        cin >> cards[i];

    //compute
    int last = 0;
    long long ans = 0;
    for (int i = 0; i < ranks; last = cards[i], i++)
        if (cards[i] > last)
            ans += cards[i] - last;

    //print and delete
    cout << ans << endl;
    delete[] cards;
    return 0;
}