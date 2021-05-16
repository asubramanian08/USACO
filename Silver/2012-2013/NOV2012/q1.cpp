// Start: 8:30
// Think: 8:36
// Write: ?
// Debug: 8:43
#include <iostream>
#include <string>
using namespace std;

int main(void)
{
    //read
#ifndef HOME
    freopen("clumsy.in", "r", stdin);
    freopen("clumsy.out", "w", stdout);
#endif
    string enter;
    cin >> enter;

    //process
    int count = 0, balance = 0;
    for (char ch : enter)
    {
        balance += ch == '(' ? 1 : -1;
        if (balance < 0)
        {
            count++;
            balance += 2;
        }
    }
    if (balance != 0)
        count += balance / 2;

    //print
    cout << count;
    return 0;
}