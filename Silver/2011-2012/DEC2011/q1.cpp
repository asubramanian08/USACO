// Start: 9:25
// Think: 9:35, 11:59-12:17, 12:23-
// Write: 12:23
// Debug:
#include <iostream>
#include <map>
using namespace std;

int numCows;
int *ordering[5];
int *key;

void idChange(void)
{
    //make ids and key
    map<int, int> ids;
    key = new int[numCows];
    for (int i = 0; i < numCows; i++)
    {
        ids[ordering[0][i]] = i;
        key[i] = ordering[0][i];
    }

    //change stuff
    for (int i = 0; i < 5; i++)
        for (int j = 0; j < numCows; j++)
            ordering[i][j] = ids[ordering[i][j]];
}

int main(void)
{
    //read
#ifndef HOME
    freopen("photo.in", "r", stdin);
    freopen("photo.out", "w", stdout);
#endif
    cin >> numCows;
    for (int i = 0; i < 5; i++)
    {
        ordering[i] = new int[numCows];
        for (int j = 0; j < numCows; j++)
            cin >> ordering[i][j];
    }

    //change values
    idChange();

    return 0;
}