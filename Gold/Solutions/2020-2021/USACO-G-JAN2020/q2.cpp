#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include <queue>
using namespace std;

#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))
#define MAX(X, Y) (((X) > (Y)) ? (X) : (Y))

struct trans
{
    unsigned int from;
    unsigned int to;
    unsigned int dist;
};
class compare
{
public:
    bool operator()(trans e1, trans e2)
    {
        return e1.dist > e2.dist;
    }
};
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
/*bool compare(const trans &e1, const trans &e2)
{
    return e1.dist > e2.dist;
};*/
int main(void)
{
    //cout << "Started" << endl;
    priority_queue<trans, std::vector<trans>, compare> bestTrans;
    unsigned int numCows = getNum(), breeds = getNum();
    //cout << "got it! " << breeds << endl;
    unsigned int *cows = new unsigned int[numCows];
    for (unsigned int i = 0; i < numCows; i++)
        cows[i] = getNum();
    //cout << "got it!" << endl;
    char ch;
    bool **talkMatrix = new bool *[breeds];
    for (unsigned int i = 0; i < breeds; i++)
    {
        //cout << i << endl;
        talkMatrix[i] = new bool[breeds];
        for (unsigned int j = 0; j < breeds; j++)
        {
            //ch = getchar();
            ch = getchar();
            if (ch == '1')
                talkMatrix[i][j] = true;
            else
                talkMatrix[i][j] = false;
        }
        /*if (i + 1 < breeds)
            getchar();*/
        getchar(); //new line
        //cin >> ch;
        //cin.get(ch); //newline
        //cout << "ok " << i << endl;
    }
    printf("got matrix");
    unsigned int *bestToHere = new unsigned int[numCows];
    for (unsigned int i = 0; i < numCows; i++)
        bestToHere[i] = ~0;
    bestToHere[0] = 0;
    trans currTrans, makeTrans;
    makeTrans.dist = 0;
    makeTrans.from = 0;
    makeTrans.to = 0;
    bestTrans.push(makeTrans);
    while (bestToHere[numCows - 1] == ~0)
    {
        currTrans = bestTrans.top();
        bestTrans.pop();
        bestToHere[currTrans.to] = bestToHere[currTrans.from] + currTrans.dist;
        for (unsigned int i = 0; i < numCows; i++)
            if (talkMatrix[cows[currTrans.to]][cows[i]] && bestToHere[i] == ~0)
            {
                makeTrans.from = currTrans.to;
                makeTrans.to = i;
                makeTrans.dist = abs((int)currTrans.to - (int)i);
                bestTrans.push(makeTrans);
            }
    }
    printf("%d", bestToHere[numCows - 1]);
    return 0;
}