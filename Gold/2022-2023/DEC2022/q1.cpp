// Official: Correct
#include <iostream>
#include <algorithm>
using namespace std;
#define f first
#define s second

int main(void)
{
    ios_base::sync_with_stdio(false);
    int n, mooney, cones;
    cin >> n >> mooney >> cones;
    pair<int, pair<int, int>> friends[2010];
    for (int i = 0; i < n; i++)
        cin >> friends[i].s.f >> friends[i].s.s >> friends[i].f;
    sort(friends, friends + n);
    int coneKS[2010][2010], mooneyKS[2010][2010];
    for (int i = 0; i < 2010; i++)
        coneKS[0][i] = mooneyKS[0][i] = 0;
    auto coneCost = [&](int idx)
    { return friends[idx].s.s * friends[idx].f; };
    for (int i = 1; i <= n; i++)
    {
        for (int j = 0; j < 2010; j++)
            coneKS[i][j] = coneKS[i - 1][j],
            mooneyKS[i][j] = mooneyKS[i - 1][j];
        for (int j = coneCost(i - 1); j < cones; j++)
            coneKS[i][j] = max(coneKS[i][j], coneKS[i - 1][j - coneCost(i - 1)] + friends[i - 1].s.f);
        for (int j = 0; j < friends[i - 1].s.s; j++)
            if (int remCones = (friends[i - 1].s.s - j) * friends[i - 1].f; cones >= remCones)
                mooneyKS[i][j] = max(mooneyKS[i][j], coneKS[i - 1][cones - remCones] + friends[i - 1].s.f);
        for (int j = friends[i - 1].s.s; j <= mooney; j++)
            mooneyKS[i][j] = max(mooneyKS[i][j], mooneyKS[i - 1][j - friends[i - 1].s.s] + friends[i - 1].s.f);
    }
    cout << mooneyKS[n][mooney] << endl;
    return 0;
}