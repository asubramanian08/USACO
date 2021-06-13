#include <iostream>
#include <set>
#include <algorithm>
using namespace std;

typedef pair<int, int> point;
#define x first
#define y second
typedef pair<int, int> pii;
#define mp make_pair

point *squares;
int sideLen;

int findOverlap(int sqr1, int sqr2)
{
    int xDist, yDist, sqr1_high, sqr1_low, sqr2_high, sqr2_low;
    //geting xDist
    sqr1_high = squares[sqr1].x + sideLen / 2;
    sqr1_low = squares[sqr1].x - sideLen / 2;
    sqr2_high = squares[sqr2].x + sideLen / 2;
    sqr2_low = squares[sqr2].x - sideLen / 2;
    if ((sqr1_high > sqr2_high) && (sqr1_low < sqr2_high))
        xDist = sqr2_high - sqr1_low;
    else
        xDist = sqr1_high - sqr2_low;
    //getting yDist
    sqr1_high = squares[sqr1].y + sideLen / 2;
    sqr1_low = squares[sqr1].y - sideLen / 2;
    sqr2_high = squares[sqr2].y + sideLen / 2;
    sqr2_low = squares[sqr2].y - sideLen / 2;
    if ((sqr1_high > sqr2_high) && (sqr1_low < sqr2_high))
        yDist = sqr2_high - sqr1_low;
    else
        yDist = sqr1_high - sqr2_low;
    //return
    return xDist * yDist;
}

int main(void)
{
    //read
    FILE *junk;
    junk = freopen("squares.in", "r", stdin);
    junk = freopen("squares.out", "w", stdout);
    int numSquares;
    cin >> numSquares >> sideLen;
    squares = new point[numSquares];
    for (int i = 0; i < numSquares; i++)
        cin >> squares[i].x >> squares[i].y;

    //sweep line
    sort(&squares[0], &squares[numSquares]);
    set<pii> onY;
    int inRange = 0, overlap = 0;
    onY.insert(mp(squares[0].y + sideLen / 2, 0));
    onY.insert(mp(squares[0].y - sideLen / 2, 0));
    for (int i = 1; i < numSquares; i++)
    {
        //keep up the onY
        while ((inRange < i) && (squares[i].x - squares[inRange].x >= sideLen))
        {
            onY.erase(mp(squares[inRange].y + sideLen / 2, inRange));
            onY.erase(mp(squares[inRange].y - sideLen / 2, inRange));
            inRange++;
        }

        //find the overlap
        auto lowPos = onY.lower_bound(mp(squares[i].y - sideLen / 2, numSquares));
        auto hiPos = onY.lower_bound(mp(squares[i].y + sideLen / 2, 0));
        if (*hiPos != *lowPos)
        {
            //2 overlaping places
            if ((*lowPos != *(--hiPos)) || (overlap != 0))
            {
                overlap = -1;
                break;
            }
            int otherSqr = (*lowPos).second;
            overlap = findOverlap(i, otherSqr);
        }

        //insert this one
        onY.insert(mp(squares[i].y + sideLen / 2, i));
        onY.insert(mp(squares[i].y - sideLen / 2, i));
    }

    //delete and print
    delete[] squares;
    cout << overlap;
    return 0;
}