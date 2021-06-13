#include <stdio.h>
#include <stdlib.h>
#include <string.h>

using namespace std;

#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))
#define MAX(X, Y) (((X) > (Y)) ? (X) : (Y))
unsigned long long getNum()
{
    unsigned long long total = 0;
    char ch = getchar();
    while ((ch != ' ') && (ch != '\n'))
    {
        total = (total * 10) + (ch - '0');
        ch = getchar();
    }
    return total;
}

int main(void)
{
    unsigned int blocks = getNum();
    char *orgStr = (char *)malloc(sizeof(char) * blocks);
    for (unsigned int i = 0; i < blocks; i++)
    {
        orgStr[i] = getchar();
        getchar(); //newline
    }
    char *newStr = (char *)malloc(sizeof(char) * blocks);
    unsigned int top = 0, bottem = blocks - 1, t2, b2;
    for (unsigned int i = 0; top < bottem; i++)
    {
        t2 = top;
        b2 = bottem;
        while ((b2 - t2 > 1) && (orgStr[t2] == orgStr[b2]))
        {
            b2--;
            t2++;
        }
        if (orgStr[t2] < orgStr[b2])
        {
            newStr[i] = orgStr[top];
            top++;
        }
        else
        {
            newStr[i] = orgStr[bottem];
            bottem--;
        }
    }
    newStr[blocks - 1] = orgStr[top];
    for (unsigned int i = 0; i < blocks; i++)
    {
        if ((i % 80 == 0) && (i != 0))
            printf("\n");
        printf("%c", newStr[i]);
    }
    return 0;
}