// Start: 8:43
// Think: 9:07
// Write: 9:43
// Debug: 11:13
#include <iostream>
using namespace std;

#define BIG_NUM 1000000000
long long ans, total1, total2, ones1, ones2;
int arrLen, *arr1, *arr2;

void switching(bool sType, int cng) //0 if 0-1 and 1 if 1-0
{
    long long diff = total1 - total2, cost = 0;
    for (int pos1 = arrLen - 1, pos2 = 0; pos1 >= 0; pos1--)
    {
        if (arr1[pos1] != sType)
            continue;
        while (arr2[pos2] == sType)
            if (pos2 == arrLen - 1)
                return;
            else
                pos2++;
        cost += (arrLen - 1 - pos1) + pos2 + 1;
        diff += cng * (arrLen - 1 - pos1) - (cng * pos2) + cng * (arrLen - ones1 - ones2);
        ans = min(ans, abs(diff) + cost);
        pos2++;
        if (pos2 == arrLen)
            return;
    }
}

int main(void)
{
    //read
#ifndef HOME
    freopen("balance.in", "r", stdin);
    freopen("balance.out", "w", stdout);
#endif
    cin >> arrLen;
    arr1 = new int[arrLen];
    for (int i = 0; i < arrLen; i++)
        cin >> arr1[i];
    arr2 = new int[arrLen];
    for (int i = 0; i < arrLen; i++)
        cin >> arr2[i];

    //total and # of ones
    total1 = ones1 = 0;
    for (int i = 0; i < arrLen; i++)
        if (arr1[i] == 1)
            ones1++;
        else
            total1 += ones1;
    total2 = ones2 = 0;
    for (int i = 0; i < arrLen; i++)
        if (arr2[i] == 1)
            ones2++;
        else
            total2 += ones2;

    //cost of noSwitch, 0-1, and 1-0
    ans = abs(total1 - total2);
    switching(0, 1);
    switching(1, -1);

    //print and delete
    cout << ans << endl;
    delete[] arr1;
    delete[] arr2;
    return 0;
}