// Start: 9:25
// Think: 9:35, 11:59-12:17, 12:23- ~1:00
// Write: 12:23
// Debug:

//after looking at solution: 2:30-2:46
#include <iostream>
#include <map>
#include <algorithm>
using namespace std;

#define numPictures 5
map<int, int> pos[numPictures];
bool cmpPos(int cow1, int cow2)
{
    int before = 0, after = 0;
    for (int i = 0; i < numPictures; i++)
        if (pos[i][cow1] < pos[i][cow2])
            before++;
        else
            after++;
    return before > after;
}

int main(void)
{
    //read
#ifndef HOME
    freopen("photo.in", "r", stdin);
    freopen("photo.out", "w", stdout);
#endif
    int numCows, cow;
    int *ordering = new int[numCows];
    cin >> numCows;
    for (int i = 0; i < numPictures; i++)
        for (int j = 0; j < numCows; j++)
        {
            cin >> cow;
            pos[i][cow] = j;
            ordering[j] = cow;
        }

    //get the ordering, delete and print
    sort(&ordering[0], &ordering[numCows], cmpPos);
    for (int i = 0; i < numCows; i++)
        cout << ordering[i] << endl;
    delete[] ordering;
    return 0;
}