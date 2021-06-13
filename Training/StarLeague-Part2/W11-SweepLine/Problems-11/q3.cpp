#include <iostream>
#include <algorithm>
#include <set>
using namespace std;

typedef pair<int, int> point;
#define x first
#define y second
typedef pair<point, point> hill;
struct eventPoint
{
    point pt;
    int hillNum;
    bool is_start;
};

#define mp make_pair
bool cmp_ep(const eventPoint &ep1, const eventPoint &ep2)
{
    if (ep1.pt.x != ep2.pt.x)
        return ep1.pt.x < ep2.pt.x;
    if (ep1.is_start != ep2.is_start)
        return ep1.is_start;
    return ep1.pt.y < ep2.pt.y;
    //return ep1.pt < ep2.pt;
}
hill *hills;
typedef long long ll;
class cmp_pt
{
public:
    bool operator()(const int &p1, const int &p2) const
    {
        int xPos = max(hills[p1].first.x, hills[p2].first.x);
        double slope1 = (double)(hills[p1].first.y - hills[p1].second.y) /
                        (double)(hills[p1].first.x - hills[p1].second.x);
        double high1 = slope1 * (double)(xPos - hills[p1].first.x) + (double)hills[p1].first.y;
        double slope2 = (double)(hills[p2].first.y - hills[p2].second.y) /
                        (double)(hills[p2].first.x - hills[p2].second.x);
        double high2 = slope2 * (double)(xPos - hills[p2].first.x) + (double)hills[p2].first.y;
        return high1 > high2;
    }
};

int main(void)
{
    //read
    FILE *junk;
    junk = freopen("hillwalk.in", "r", stdin);
    junk = freopen("hillwalk.out", "w", stdout);
    int numHills;
    cin >> numHills;
    hills = new hill[numHills];
    for (int i = 0; i < numHills; i++)
        cin >> hills[i].first.x >> hills[i].first.y >>
            hills[i].second.x >> hills[i].second.y;

    //setup Data Structures
    eventPoint *points = new eventPoint[numHills * 2];
    for (int i = 0; i < numHills; i++)
    {
        points[i * 2].pt = hills[i].first;
        points[i * 2].hillNum = i;
        points[i * 2].is_start = true;

        points[i * 2 + 1].pt = hills[i].second;
        points[i * 2 + 1].hillNum = i;
        points[i * 2 + 1].is_start = false;
    }
    sort(&points[0], &points[numHills * 2], cmp_ep);
    set<int, cmp_pt> linesOn;

    //find the hills touched and print
    //loops through eventPoints
    int currHill = 0, hillCount = 1;
    for (int i = 0; i < numHills * 2; i++)
        if (points[i].is_start)
            linesOn.insert(points[i].hillNum);
        else
        {
            linesOn.erase(points[i].hillNum);
            if (points[i].hillNum != currHill)
                continue;
            auto line = linesOn.lower_bound(points[i].hillNum);
            if (line == linesOn.end())
                break;
            currHill = *line;
            hillCount++;
        }
    cout << hillCount;
    return 0;
}