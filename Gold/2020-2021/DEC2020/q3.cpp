// Start: 6:18
// Think:
// Write:
// Debug:
// After looking at sol: NA
#include <iostream>
#include <algorithm>
#include <set>
#include <vector>
using namespace std;

using cow = pair<int, int>;
#define x first
#define y second
#define BIG_NUM 1000000000

int numCows, ans = 0, squares = 0;
void solveSquare(cow *cows)
{
    int len, high, low, lPos, gPos;
    sort(cows, cows + numCows);
    for (int i = 0; i < numCows; i++)
    {
        set<int> y_on;
        for (int j = i + 1; j < numCows; j++)
        {
            if (i < j - 1)
                y_on.insert(cows[j - 1].y);
            len = cows[j].x - cows[i].x;
            low = max(cows[i].y, cows[j].y) - len;
            high = min(cows[i].y, cows[j].y);
            if (low > high)
                continue;

            vector<int> ys(y_on.begin(), y_on.end());
            int l = 0, r = -1;
            while (l < ys.size() && low >= ys[l] + 1)
                l++;
            while (r + 1 < ys.size() && low >= ys[r + 1] - len)
                r++;

            while (true)
            {
                ++ans;
                int yl = min(cows[i].y, cows[j].y), yr = max(cows[i].y, cows[j].y);
                if (l <= r)
                    yl = min(yl, ys[l]), yr = max(yr, ys[r]);
                squares += yr - yl == len;
                int leave_bottom = (l < ys.size() ? ys[l] + 1 : BIG_NUM);
                int enter_top = (r + 1 < ys.size() ? ys[r + 1] - len : BIG_NUM);
                int change_y = min(leave_bottom, enter_top);
                if (change_y > high)
                    break;
                l += leave_bottom == change_y;
                r += enter_top == change_y;
            }
        }
    }
}

int main(void)
{
    //read
    cin >> numCows;
    cow *cows = new cow[numCows];
    for (int i = 0; i < numCows; i++)
        cin >> cows[i].x >> cows[i].y;

    solveSquare(cows);
    for (int i = 0; i < numCows; i++)
        swap(cows[i].x, cows[i].y);
    solveSquare(cows);
    ans -= squares / 2;
    ans += numCows + 1;

    //print and delete
    cout << ans << endl;
    delete[] cows;
    return 0;
}