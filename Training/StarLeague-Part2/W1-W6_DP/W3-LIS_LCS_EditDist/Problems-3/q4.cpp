#include <string>
#include <iostream>
using namespace std;

struct nameSwitch
{
    string from;
    string to;
};

int main(void)
{
    FILE *junk;
    junk = freopen("cowlist.in", "r", stdin);
    junk = freopen("cowlist.out", "w", stdout);
    int changes;
    cin >> changes;
    nameSwitch *listing = new nameSwitch[changes];
    for (int i = 0; i < changes; i++)
        cin >> listing[i].from >> listing[i].to;
    int costDel, costIns, costRep[2];
    cin >> costDel >> costIns >> costRep[0];
    costRep[1] = 0;
    int ans = 0;
    int DP[505][505];
    DP[0][0] = 0;
    for (int i = 1; i < 505; i++)
    {
        DP[0][i] = DP[0][i - 1] + costDel;
        DP[i][0] = DP[i - 1][0] + costIns;
    }
    bool same;
    for (int i = 0; i < changes; i++)
    {
        for (int j = 1; j <= listing[i].to.length(); j++)
            for (int k = 1; k <= listing[i].from.length(); k++){
                same = listing[i].to[j - 1] == listing[i].from[k - 1];
                DP[j][k] = min(DP[j - 1][k] + costIns,
                               min(DP[j][k - 1] + costDel,
                                   DP[j - 1][k - 1] + costRep[same]));
            };
        ans += DP[listing[i].to.length()][listing[i].from.length()];
    }
    cout << ans;
    return 0;
}