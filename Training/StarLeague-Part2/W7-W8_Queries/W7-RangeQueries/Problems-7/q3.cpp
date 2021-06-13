#include <iostream>
#include <algorithm>
#include <cmath>
using namespace std;
typedef pair<int, int> point;
struct board
{
    point pt1, pt2;
    bool is_start;
    int brd_num;
};

//Square root decomposition (min)
#define BIG_NUM 1000000000
class SQRT
{
private:
    int *SQRTarr;
    int *block;
    int arrLen, blockLen, block_sz;

public:
    SQRT(int sz);
    void updt(int idx, int val);
    int query(int idx);
    ~SQRT();
};
SQRT::SQRT(int sz)
{
    arrLen = sz;
    block_sz = sqrt(arrLen);
    blockLen = block_sz + ((arrLen % block_sz) != 0);

    SQRTarr = new int[arrLen];
    for (int i = 0; i < arrLen; i++)
        SQRTarr[i] = 0;

    block = new int[blockLen];
    for (int i = 0; i < blockLen; i++)
        block[i] = 0;
}
void SQRT::updt(int idx, int val)
{
    if (SQRTarr[idx] <= val)
        return;
    SQRTarr[idx] = val;
    block[idx / block_sz] = min(block[idx / block_sz], val);
}
int SQRT::query(int idx)
{
    int ans = BIG_NUM;
    for (int i = idx / block_sz - 1; i >= 0; i--)
        ans = min(ans, block[i]);
    for (int i = (idx / block_sz) * block_sz; i <= idx; i++)
        ans = min(ans, SQRTarr[i]);
    return ans;
}
SQRT::~SQRT()
{
    delete[] SQRTarr;
    delete[] block;
}

int *end_y;
int numBoards;
int cmpBoard(const void *p1, const void *p2)
{
    int rtn = ((board *)p1)->pt1.first - ((board *)p2)->pt1.first;
    if (rtn == 0)
        rtn = ((board *)p1)->pt1.second - ((board *)p2)->pt1.second;
    return rtn;
}
int cmpY(const void *p1, const void *p2)
{
    return *((int *)p1) - *((int *)p2);
}
int lbound(int val)
{
    // int low = 0, high = numBoards - 1;
    // if (end_y[low] >= val)
    //     high = low;
    // while (high - low > 1)
    //     if (end_y[(high + low) / 2] < val)
    //         low = (high + low) / 2;
    //     else
    //         high = (high + low) / 2;
    // return high;
    return lower_bound(&end_y[0], &end_y[numBoards], val) - &end_y[0];
}

int main(void)
{
    FILE *junk;
    junk = freopen("boards.in", "r", stdin);
    junk = freopen("boards.out", "w", stdout);
    //read
    int goal;
    cin >> goal >> numBoards;
    int totalBoards = numBoards + 1;
    int numPoints = totalBoards * 2;
    board *points = new board[numPoints];
    end_y = new int[totalBoards];
    for (int i = 0; i < numBoards; i++)
    {
        cin >> points[i * 2].pt1.first >> points[i * 2].pt1.second >>
            points[i * 2].pt2.first >> points[i * 2].pt2.second;
        points[i * 2].is_start = true;
        points[i * 2].brd_num = i;

        points[i * 2 + 1].pt1 = points[i * 2].pt2;
        points[i * 2 + 1].pt2 = points[i * 2].pt1;
        points[i * 2 + 1].is_start = false;
        points[i * 2 + 1].brd_num = i;

        end_y[i] = points[i * 2].pt2.second;
    }
    //end point
    points[numBoards * 2].is_start = true;
    points[numBoards * 2].brd_num = numBoards;
    points[numBoards * 2].pt1 = make_pair(goal, goal);
    points[numBoards * 2].pt2 = make_pair(goal, goal);
    points[numBoards * 2 + 1] = points[numBoards * 2];
    points[numBoards * 2 + 1].is_start = false;
    end_y[numBoards] = goal;

    //sorting & SQRT
    qsort(end_y, totalBoards, sizeof(int), cmpY);
    qsort(points, numPoints, sizeof(board), cmpBoard);
    SQRT costReduce(totalBoards);

    //main loop
    int queryVal;
    int *costToStart = new int[totalBoards];
    for (int i = 0; i < numPoints; i++)
        if (points[i].is_start)
            costToStart[points[i].brd_num] = costReduce.query(lbound(points[i].pt1.second));
        else
        {
            costReduce.updt(lbound(points[i].pt1.second),
                            costToStart[points[i].brd_num] +
                                (points[i].pt2.first - points[i].pt1.first) +
                                (points[i].pt2.second - points[i].pt1.second));
        }

    //get ans and print
    int ans = 2 * goal + costToStart[numBoards];
    cout << ans;
    return 0;
}