// Start: 4:00
// Think: 4:07
// Write: 4:25
// Debug: 4:25
#include <iostream>
using namespace std;

#define NA -1
using node = pair<int, int>;
int dirLen;
node *ports;
char *seq;

int doSeq(int pos)
{
    for (int i = 0; i < dirLen; i++)
        pos = (seq[i] == 'L' ? ports[pos].first : ports[pos].second) - 1;
    return pos;
}

int main(void)
{
    //read
#ifndef HOME
    freopen("cruise.in", "r", stdin);
    freopen("cruise.out", "w", stdout);
#endif
    int numPorts, loop;
    cin >> numPorts >> dirLen >> loop;
    ports = new node[numPorts];
    for (int i = 0; i < numPorts; i++)
        cin >> ports[i].first >> ports[i].second;
    seq = new char[dirLen];
    for (int i = 0; i < dirLen; i++)
        cin >> seq[i];

    //set up
    int *getTo = new int[numPorts];
    for (int i = 0; i < numPorts; i++)
        getTo[i] = NA;
    int pos = 0, seqNum;

    //find cycle
    for (seqNum = 0; getTo[pos] == NA; seqNum++)
    {
        getTo[pos] = seqNum;
        pos = doSeq(pos);
    }

    //do the cycles left
    int left = (loop - getTo[pos]) % (seqNum - getTo[pos]);
    for (int i = 0; i < left; i++)
        pos = doSeq(pos);

    //print and delete
    cout << pos + 1 << endl;
    delete[] ports;
    delete[] seq;
    delete[] getTo;
    return 0;
}