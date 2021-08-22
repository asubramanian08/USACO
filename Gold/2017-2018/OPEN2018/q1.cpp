// Start: 8:17
// Think: 8:38, 10:03-10:30,NA
// Write:
// Debug:
// After looking at sol: 12:44-12:50
#include <iostream>
#include <algorithm>
using namespace std;

using pii = pair<int, int>;

int main(void)
{
    //read
#ifndef HOME
    freopen("sort.in", "r", stdin);
    freopen("sort.out", "w", stdout);
#endif
    int numEle;
    cin >> numEle;
    pii *list = new pii[numEle];
    for (int i = 0; i < numEle; i++)
    {
        cin >> list[i].first;
        list[i].second = i;
    }

    //prep
    sort(list, list + numEle);
    bool *saw = new bool[numEle];
    for (int i = 0; i < numEle; i++)
        saw[i] = false;

    //crossed line
    int ans = 1, curr = 0;
    for (int i = 0; i < numEle; i++)
    {
        saw[list[i].second] = true;
        curr += saw[i] == false;
        curr -= list[i].second < i;
        ans = max(ans, curr);
    }

    //print and delete
    cout << ans << endl;
    delete[] list;
    delete[] saw;
    return 0;
}