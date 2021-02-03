#include <stdio.h>
#include <stdlib.h>
#include <string.h>
using namespace std;

#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))
#define MAX(X, Y) (((X) > (Y)) ? (X) : (Y))
long long getNum()
{
    long long total = 0;
    char ch = getchar();
    if (ch == '-')
        return getNum() * -1;
    while ((ch >= '0') && (ch <= '9'))
    {
        total = (total * 10) + (ch - '0');
        ch = getchar();
    }
    return total;
}

int main(void)
{

    return 0;
}