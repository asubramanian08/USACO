// Start: 8:07
// Think: 8:43, 11:13-NA
// Write:
// Debug:
// After looking at sol: 1:36-1:44
#include <iostream>
#include <stack>
using namespace std;

#define NA -1

int main(void)
{
    //read
#ifndef HOME
    freopen("dishes.in", "r", stdin);
    freopen("dishes.out", "w", stdout);
#endif
    int numDishes;
    cin >> numDishes;
    int *dishes = new int[numDishes];
    for (int i = 0; i < numDishes; i++)
        cin >> dishes[i];

    //set up
    int *base = new int[numDishes];
    for (int i = 0; i < numDishes; i++)
        base[i] = NA;
    stack<int> *soapy = new stack<int>[numDishes];

    //run though dishes and print
    int topStack = 0;
    for (int i = 0; i < numDishes; i++)
    {
        if (dishes[i] < topStack)
        {
            cout << i << endl;
            return 0;
        }
        for (int j = dishes[i]; j > 0 && base[j] == NA; j--)
            base[j] = dishes[i];
        while (!soapy[base[dishes[i]]].empty() && soapy[base[dishes[i]]].top() < dishes[i])
        {
            topStack = soapy[base[dishes[i]]].top();
            soapy[base[dishes[i]]].pop();
        }
        soapy[base[dishes[i]]].push(dishes[i]);
    }
    cout << numDishes << endl;

    //delete
    delete[] dishes;
    delete[] base;
    delete[] soapy;
    return 0;
}