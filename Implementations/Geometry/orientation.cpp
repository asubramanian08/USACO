#include <utility>
using namespace std;
typedef pair<int, int> point;
#define x first
#define y second

typedef long long ll;
int orient(point &p1, point &p2, point &p3)
{
    ll val = (ll)(p2.y - p1.y) * (ll)(p3.x - p2.x) -
             (ll)(p2.x - p1.x) * (ll)(p3.y - p2.y);

    if (val == 0)
        return 0;
    return (val > 0) ? -1 : 1;
}