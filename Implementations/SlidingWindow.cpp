// AlphaStar-PlatinumA week 2 q1
#include <iostream>
#include <deque>
using namespace std;

int main(void)
{
    using pli = pair<long long, int>;
    deque<pli> d;
    d.push_back(pli(0, -1));
    for (int i = 0; i < loop; i++)
    {
        while (!d.empty() && d.front().second + maxJump < i)
            d.pop_front();
        // do stuff
        while (!d.empty() && /*better*/)
            d.pop_back();
        d.push_back(pli(/*pos, value*/));
    }
    return 0;
}