// 6:45 - 6:54 - 7:14 + hint to use hash_map
#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
using namespace std;

int flavors[50'000][5], n;
class vecCmp
{
public:
    size_t operator()(std::vector<int> const &vec) const
    {
        size_t seed = vec.size();
        for (const auto &i : vec)
            seed ^= i + 0x9e3779b9 + (seed << 6) + (seed >> 2);
        return seed;
    }
};

int main(void)
{
#ifndef HOME
    freopen("cowpatibility.in", "r", stdin);
    freopen("cowpatibility.out", "w", stdout);
#endif
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < 5; j++)
            cin >> flavors[i][j];
        sort(flavors[i], flavors[i] + 5);
    }
    unordered_map<vector<int>, int, vecCmp> cowsCount;
    long long ans = 0;
    int ks[5] = {1, 2, 4, 8, 16};
    for (int i = 0; i < n; i++)
    {
        int cowsUsed = 0;
        for (int j = 1; j < 32; j++)
        {
            vector<int> flavorLikings;
            for (int k = 0; k < 5; k++)
                if (j & ks[k])
                    flavorLikings.push_back(flavors[i][k]);
            if (flavorLikings.size() % 2)
                cowsUsed += cowsCount[flavorLikings]++;
            else
                cowsUsed -= cowsCount[flavorLikings]++;
        }
        ans += i - cowsUsed;
    }
    cout << ans << endl;
}