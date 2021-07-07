//this is converting a DAG into an array to be processed with things like shortest path
//the property of a topological sort is that all a nodes ancestors are to the left of it
//look at starleague part 1 lesson 9 which is all about DAGs (essentially just topological order)

#include <vector>
#include <queue>
using namespace std;
int main(void) //this is a topological loop, but doesn't make a topilocal ordering vector
{
    int numNodes;
    vector<int> *graph;
    int *inDeg; //in degree, the number of connections to land at a node

    queue<int> q;
    for (int i = 0; i < numNodes; i++)
        if (inDeg[i] == 0)
            q.push(i);
    int node;
    while (!q.empty())
    {
        node = q.front();
        q.pop();
        //do whatever topologically ordered thing you need to do here
        for (auto next : graph[node])
            if (--inDeg[next] == 0)
                q.push(next);
    }
    //if there are still inDegs that are greater then 0, the graph has cycles
}