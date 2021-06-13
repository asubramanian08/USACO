#include <iostream>
#include <cmath>
using namespace std;

typedef long long ll;
typedef long double ld;
#define SQRT(x) ((ld)sqrt((ld)abs(x)))
#define MIN_Y(leg1, leg2) (ll) SQRT(pow(leg1, 2) - pow(leg2, 2))
#define MAX_Y(leg1, leg2) (ll) ceil(SQRT(pow(leg1, 2) - pow(leg2, 2)))
long long GCD(long long num1, long long num2)
{
    long long temp;
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
    /*FILE *junk;
    junk = freopen("banner.in", "r", stdin);
    junk = freopen("banner.out", "w", stdout);*/
    ll xRange, yRange, banMin, banMax;
    cin >> xRange >> yRange >> banMin >> banMax;

    //find disk -> find line -> find number of lines that apply
    //calc total (based on things about) and print5
    ll total = 0, max_x, max_y, x, y, yStart;
    max_x = min(banMax, xRange);
    for (x = 0; x <= max_x; x++)
    {
        max_y = min(MIN_Y(banMax, x), yRange);
        if (x > banMin)
            yStart = 0;
        else
            yStart = MAX_Y(banMin, x);
        for (y = yStart; y <= max_y; y++)
            //doesn't go through other latice points
            if (x && y)
            {
                if (GCD(x, y) <= 1)
                    total += 2 * (xRange - x + 1) * (yRange - y + 1); // '\' and '/'
            }
            else if (x + y == 1)
                total += (xRange - x + 1) * (yRange - y + 1); //no fliping
    }
    cout << total << endl;
    return 0;
}