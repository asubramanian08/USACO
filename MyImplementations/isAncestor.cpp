#include <vector>
using namespace std;

//ancestor decedent relationship
class ADR
{
private:
    int *inTime;
    int *outTime;
    int Time, numElements;
    vector<int> *conns;
    void findTimes(int node, int parent);

public:
    ADR() {}
    ADR(vector<int> *conns, int n_ele);
    bool isAns(int node, int parent);
};
void ADR::findTimes(int node, int parent)
{
    inTime[node] = ++Time;
    for (int i = 0; i < conns[node].size(); i++)
        if (conns[node][i] != parent)
            findTimes(conns[node][i], node);
    outTime[node] = ++Time;
}
bool ADR::isAns(int node, int parent)
{
    return (inTime[parent] <= inTime[node]) &&
           (outTime[parent] >= outTime[node]);
}
ADR::ADR(vector<int> *conns_, int n_ele)
{
    conns = conns_;
    numElements = n_ele;
    inTime = new int[numElements];
    outTime = new int[numElements];
    Time = 0;
    findTimes(0, -1);
}