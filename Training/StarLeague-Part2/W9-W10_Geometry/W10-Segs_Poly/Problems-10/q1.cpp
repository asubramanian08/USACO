#include <iostream>
#include <cmath>
using namespace std;

#define f first
#define s second
typedef pair<int, int> point;
int GCD(int num1, int num2)
{
    int temp;
    while (num2)
    {
        temp = num2;
        num2 = num1 % num2;
        num1 = temp;
    }
    return num1;
}

int main(void)
{
    //read
    FILE *junk;
    junk = freopen("fence9.in", "r", stdin);
    junk = freopen("fence9.out", "w", stdout);
    point p1;
    int p2;
    cin >> p1.first >> p1.second >> p2;

    //calculate and print
    int fencePoints = p2 + GCD(p1.f, p1.s) + GCD(abs(p1.f - p2), p1.s);
    double area = (p2 * p1.s) / 2;
    int insidePoints = area - (double)fencePoints / 2 + 1;
    cout << insidePoints;
    return 0;
}