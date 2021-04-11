#include <algorithm>
using namespace std;

//min decomposition
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
        SQRTarr[i] = BIG_NUM;

    block = new int[blockLen];
    for (int i = 0; i < blockLen; i++)
        block[i] = BIG_NUM;
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