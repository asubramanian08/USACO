// Start: 11:19
// Think: 11:44
// Write: 12:35
// Debug: 12:45 AND TILL 1:52 -> 12/15
#include <iostream>
#include <cmath>
#include <algorithm>
using namespace std;

//sqrt (max)
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
    if (SQRTarr[idx] >= val)
        return;
    SQRTarr[idx] = val;
    block[idx / block_sz] = max(block[idx / block_sz], val);
}
int SQRT::query(int idx)
{
    int ans = 0;
    for (int i = idx / block_sz - 1; i >= 0; i--)
        ans = max(ans, block[i]);
    for (int i = (idx / block_sz) * block_sz; i <= idx; i++)
        ans = max(ans, SQRTarr[i]);
    return ans;
}
SQRT::~SQRT()
{
    delete[] SQRTarr;
    delete[] block;
}

struct board
{
    int x1, y1;
    int x2, y2;
    int saved;
    bool operator<(const board &b) const { return x2 < b.x2; }
};
using ep = pair<int, bool>;
using pii = pair<int, int>;

int main(void)
{
    //read
#ifndef HOME
    freopen("boards.in", "r", stdin);
    freopen("boards.out", "w", stdout);
#endif
    int gridLen, numBoards;
    cin >> gridLen >> numBoards;
    board *boards = new board[numBoards];
    for (int i = 0; i < numBoards; i++)
    {
        cin >> boards[i].x1 >> boards[i].y1 >> boards[i].x2 >> boards[i].y2;
        boards[i].saved = 0;
    }

    //prep
    sort(boards, boards + numBoards);
    SQRT sqrt(numBoards);
    ep *eps = new ep[numBoards * 2];
    for (int i = 0; i < numBoards; i++)
    {
        eps[i] = {i, true}; //first
        eps[i + numBoards] = {i, false};
    }
    sort(eps, eps + numBoards * 2, [boards](ep e1, ep e2)
         {
             pii p1 = e1.second ? pii(boards[e1.first].x1, boards[e1.first].y1)
                                : pii(boards[e1.first].x2, boards[e1.first].y2);
             pii p2 = e2.second ? pii(boards[e2.first].x1, boards[e2.first].y1)
                                : pii(boards[e2.first].x2, boards[e2.first].y2);
             return p1.second == p2.second ? p1.first < p2.first : p1.second < p2.second;
         });

    //go though events
    board temp;
    int pos;
    for (int i = 0; i < numBoards * 2; i++)
        if (eps[i].second == false)
            sqrt.updt(eps[i].first, boards[eps[i].first].saved +
                                        (boards[eps[i].first].x2 - boards[eps[i].first].x1) +
                                        (boards[eps[i].first].y2 - boards[eps[i].first].y1));
        else
        {
            temp.x2 = boards[eps[i].first].x1;
            pos = lower_bound(boards, boards + numBoards, temp) - boards;
            boards[eps[i].first].saved = sqrt.query(pos);
        }

    //print and delete
    cout << 2 * gridLen - sqrt.query(numBoards - 1);
    delete[] boards;
    delete[] eps;
    return 0;
}