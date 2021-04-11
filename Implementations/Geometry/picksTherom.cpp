#include <cmath>
#include <utility>
using namespace std;

#define f first
#define s second
typedef pair<int, int> point;

int main(void)
{
    point p1;
    int p2;

    int fencePoints = p2 + gcd(p1.f, p1.s) + gcd(abs(p1.f - p2), p1.s);
    double area = (p2 * p1.s) / 2;
    int insidePoints = area - (double)fencePoints / 2 + 1;
}