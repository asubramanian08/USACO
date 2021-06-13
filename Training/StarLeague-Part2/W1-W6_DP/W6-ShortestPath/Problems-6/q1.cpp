#include <iostream>
#include <queue>
using namespace std;

typedef pair<int, int> point;
#define BIG_NUM 100000
#define MAX_SIDE 20 //memory too big
#define inRange(x) ((x >= 0) && (x < sideLen))
class pos
{
public:
    int dir;
    point rightPoint;
    point upPoint;
    pos(int d, const point &rp, const point &up)
    {
        dir = d;
        rightPoint = rp;
        upPoint = up;
    }
    pos(void)
    {
    }
};

int main(void)
{
    /*FILE *junk;
    junk = freopen("cownav.in", "r", stdin);
    junk = freopen("cownav.out", "w", stdout);*/

    int sideLen;
    cin >> sideLen;
    bool **grid = new bool *[sideLen];
    char ch;
    for (int i = 0; i < sideLen; i++)
    {
        grid[i] = new bool[sideLen];
        for (int j = 0; j < sideLen; j++)
        {
            cin >> ch;
            grid[i][j] = ch == 'H';
        }
    }

    //dir: 0 = up; 1 = right; 2 = down; 3 = left
    //first half is initialized for right, and second down
    //dir is for the up
    int DP[MAX_SIDE][MAX_SIDE][4][MAX_SIDE][MAX_SIDE];
    for (int i = 0; i < MAX_SIDE; i++)
        for (int j = 0; j < MAX_SIDE; j++)
            for (int k = 0; k < 4; k++)
                for (int l = 0; l < MAX_SIDE; l++)
                    for (int m = 0; m < MAX_SIDE; m++)
                        DP[i][j][k][l][m] = BIG_NUM;
    DP[sideLen - 1][0][0][sideLen - 1][0] = 0;

    queue<pos> moves;
    moves.push(pos(0, make_pair(sideLen - 1, 0), make_pair(sideLen - 1, 0)));
    pos currStates;
    while (!moves.empty())
    {
        currStates = moves.front();
        moves.pop();
        //turn right
        if (DP[currStates.rightPoint.first][currStates.rightPoint.second][(currStates.dir + 1) % 4]
              [currStates.upPoint.first][currStates.upPoint.second] >
            DP[currStates.rightPoint.first][currStates.rightPoint.second][currStates.dir]
              [currStates.upPoint.first][currStates.upPoint.second] +
                1)
        {
            DP[currStates.rightPoint.first][currStates.rightPoint.second][(currStates.dir + 1) % 4]
              [currStates.upPoint.first][currStates.upPoint.second] =
                  DP[currStates.rightPoint.first][currStates.rightPoint.second][currStates.dir]
                    [currStates.upPoint.first][currStates.upPoint.second] +
                  1;

            moves.push(pos((currStates.dir + 1) % 4, currStates.rightPoint, currStates.upPoint));
        }

        //turn left
        if (DP[currStates.rightPoint.first][currStates.rightPoint.second][(currStates.dir + 3) % 4]
              [currStates.upPoint.first][currStates.upPoint.second] >
            DP[currStates.rightPoint.first][currStates.rightPoint.second][currStates.dir]
              [currStates.upPoint.first][currStates.upPoint.second] +
                1)
        {
            DP[currStates.rightPoint.first][currStates.rightPoint.second][(currStates.dir + 3) % 4]
              [currStates.upPoint.first][currStates.upPoint.second] =
                  DP[currStates.rightPoint.first][currStates.rightPoint.second][currStates.dir]
                    [currStates.upPoint.first][currStates.upPoint.second] +
                  1;

            moves.push(pos((currStates.dir + 3) % 4, currStates.rightPoint, currStates.upPoint));
        }

        //move forward setup
        point changeUp, changeRight;
        int rightDir = (currStates.dir + 1) % 4;
        if ((currStates.rightPoint.first == 0) && (currStates.rightPoint.second == sideLen - 1))
            changeRight = make_pair(0, 0);
        else
        {
            if (rightDir % 2 == 0)
                changeRight = make_pair(rightDir - 1, 0);
            else
                changeRight = make_pair(0, -1 * (rightDir - 2));
            if (!inRange(currStates.rightPoint.first + changeRight.first) ||
                !inRange(currStates.rightPoint.second + changeRight.second) ||
                grid[currStates.rightPoint.first + changeRight.first]
                    [currStates.rightPoint.second + changeRight.second])
                changeRight = make_pair(0, 0);
        }
        if ((currStates.upPoint.first == 0) && (currStates.upPoint.second == sideLen - 1))
            changeUp = make_pair(0, 0);
        else
        {
            if (currStates.dir % 2 == 0)
                changeUp = make_pair(currStates.dir - 1, 0);
            else
                changeUp = make_pair(0, -1 * (currStates.dir - 2));
            if (!inRange(currStates.upPoint.first + changeUp.first) ||
                !inRange(currStates.upPoint.second + changeUp.second) ||
                grid[currStates.upPoint.first + changeUp.first]
                    [currStates.upPoint.second + changeUp.second])
                changeUp = make_pair(0, 0);
        }

        //move forward
        if (DP[currStates.rightPoint.first + changeRight.first][currStates.rightPoint.second + changeRight.second]
              [currStates.dir]
              [currStates.upPoint.first + changeUp.first][currStates.upPoint.second + changeUp.second] >
            DP[currStates.rightPoint.first][currStates.rightPoint.second][currStates.dir]
              [currStates.upPoint.first][currStates.upPoint.second] +
                1)
        {
            DP[currStates.rightPoint.first + changeRight.first][currStates.rightPoint.second + changeRight.second]
              [currStates.dir]
              [currStates.upPoint.first + changeUp.first][currStates.upPoint.second + changeUp.second] =
                  DP[currStates.rightPoint.first][currStates.rightPoint.second][currStates.dir]
                    [currStates.upPoint.first][currStates.upPoint.second] +
                  1;

            moves.push(pos(currStates.dir,
                           make_pair(currStates.rightPoint.first + changeRight.first,
                                     currStates.rightPoint.second + changeRight.second),
                           make_pair(currStates.upPoint.first + changeUp.first,
                                     currStates.upPoint.second + changeUp.second)));
        }
    }

    int ans = BIG_NUM;
    for (int i = 0; i < 4; i++)
        ans = min(ans, DP[0][sideLen - 1][i][0][sideLen - 1]);
    cout << ans;
    return 0;
}