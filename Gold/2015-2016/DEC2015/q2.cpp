// Start: 10:45
// Think: 10:48
// Write: 10:57
// Debug: 10:58
#include <iostream>
#include <algorithm>
using namespace std;

int main(void)
{
    //read
#ifndef HOME
    freopen("feast.in", "r", stdin);
    freopen("feast.out", "w", stdout);
#endif
    int maxFull, inc1, inc2;
    cin >> maxFull >> inc1 >> inc2;

    int *is_pos = new int[maxFull + 1 + max(inc1, inc2)];
    fill(is_pos, is_pos + maxFull + 1, false);
    is_pos[0] = true;

    //run the pre prewater
    for (int i = 0; i <= maxFull; i++)
    {
        if (!is_pos[i])
            continue;
        is_pos[i + inc1] = true;
        is_pos[i + inc2] = true;
        is_pos[i / 2] = true; //won't effect this loop
    }

    //run the post water
    int maxFill;
    for (int i = 0; i <= maxFull; i++)
    {
        if (!is_pos[i])
            continue;
        is_pos[i + inc1] = true;
        is_pos[i + inc2] = true;
        maxFill = i;
    }

    //print and delete
    cout << maxFill << endl;
    delete[] is_pos;
    return 0;
}