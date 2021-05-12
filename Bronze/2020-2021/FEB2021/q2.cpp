// Doing to stop debug time -> submit once
// Start: 8:03
// Think: 8:23
// Write: 8:37
// red the question wrong many times
#include <iostream>
using namespace std;

#define gridSide 1001
#define goal 3
int neighbors[gridSide][gridSide] = {0};
bool is_cow[gridSide][gridSide] = {false};
int comfortable = 0;

void fixComfort(int x, int y)
{
    if (neighbors[x][y] == goal)
        comfortable++;
    else if (neighbors[x][y] == goal + 1)
        comfortable--;
}
void doNeighbor(int x, int y)
{
    if ((x < 0 || x >= gridSide) || (y < 0 || y >= gridSide))
        return;
    neighbors[x][y]++;
    if (is_cow[x][y])
        fixComfort(x, y);
}

int main(void)
{
    //read
    int numCows, x, y;
    cin >> numCows;
    for (int i = 0; i < numCows; i++)
    {
        cin >> x >> y;
        is_cow[x][y] = true;
        doNeighbor(x + 1, y);
        doNeighbor(x - 1, y);
        doNeighbor(x, y + 1);
        doNeighbor(x, y - 1);
        fixComfort(x, y);
        cout << comfortable << '\n';
    }
    return 0;
}