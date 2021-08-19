#include <iostream>
#include <stack>
#include <set>
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
    stack<int> *soapy = new stack<int>[numDishes + 1];
    set<int> findBase;
    //run though dishes and print
    int topStack = 0, base;
    for (int i = 0; i < numDishes; i++)
    {
        if (dishes[i] < topStack)
        {
            cout << i << endl;
            return 0;
        }
        if (findBase.lower_bound(dishes[i]) != findBase.end())
            base = *findBase.lower_bound(dishes[i]);
        else
            findBase.insert(base = dishes[i]);
        while (!soapy[base].empty() && soapy[base].top() < dishes[i])
        {
            topStack = soapy[base].top();
            soapy[base].pop();
        }
        soapy[base].push(dishes[i]);
    }
    cout << numDishes << endl;

    //delete
    delete[] dishes;
    delete[] soapy;
    return 0;
}