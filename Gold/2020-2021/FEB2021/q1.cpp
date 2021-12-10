// Start: 8:40
// Think: 9:00, 10:10
// Write:
// Debug: 11:36
#include <iostream>
#include <vector>
using namespace std;

#define MAX_SIZE 1000001

int main(void)
{
    // read
    int numPiles;
    cin >> numPiles;
    int stoneHeight[MAX_SIZE] = {0};
    for (int i = 0; i < numPiles; i++)
    {
        int height;
        cin >> height;
        stoneHeight[height]++;
    }
    for (int i = 1; i < MAX_SIZE; i++)
        stoneHeight[i] += stoneHeight[i - 1];
    auto sumVal = [&stoneHeight](int index)
    { return stoneHeight[index >= MAX_SIZE ? MAX_SIZE - 1 : index]; };

    // calc ans
    long long ans = 0;
    int count[MAX_SIZE];
    for (int i = 1; i < MAX_SIZE; i++)
    {
        for (int j = 1; i * j < MAX_SIZE; j++)
            count[j] = sumVal(i * (j + 1) - 1) - sumVal(i * j - 1);
        vector<int> odd;
        for (int j = 1; i * j < MAX_SIZE; j++)
            if (count[j] % 2 == 1)
                odd.push_back(j);
        if (odd == vector<int>{1} || (odd.size() == 2 && odd[0] + 1 == odd[1]))
            ans += count[odd.back()];
    }

    // print
    cout << ans << endl;
    return 0;
}