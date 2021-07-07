#include <vector>
using namespace std;
//Transform a tree into an array, easier to analysis
//See star league Part 2 week 8 q4

//Euler tour
vector<int> *conns;
vector<int> ET_arr;
int *inTime;
int *outTime;
int Time;
void EulerTour(int node, int parent)
{
    ET_arr.push_back(node);
    inTime[node] = Time;
    Time++;

    for (int i = 0; i < conns[node].size(); i++)
        if (conns[node][i] != parent)
            EulerTour(conns[node][i], node);

    ET_arr.push_back(node);
    outTime[node] = Time;
    Time++;
}