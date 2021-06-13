#include <iostream>
#include <math.h>
//#include <algorithm>
using namespace std;
typedef pair<int, int> pii;
#define rangeMin(start, end, log) min(st[start][log].first, st[end - (1 << log) + 1][log].first)
#define rangeMax(start, end, log) max(st[start][log].second, st[end - (1 << log) + 1][log].second)
#define rangeDif(start, end, log) (rangeMax(start, end, log) - rangeMin(start, end, log))

int numCows;
int main(void)
{
    /*FILE *junk;
    junk = freopen("lineup.in", "r", stdin);
    junk = freopen("lineup.out", "w", stdout);*/

    //reading
    int queries;
    cin >> numCows >> queries;
    pii **st = new pii *[numCows];
    int log = log2(numCows) + 1;
    for (int i = 0; i < numCows; i++)
    {
        st[i] = new pii[log];
        cin >> st[i][0].first;
        st[i][0].second = st[i][0].first;
    }

    //set sparse table
    for (int j = 1; j < log; j++)
        for (int i = 0; i + (1 << j) <= numCows; i++)
        {
            st[i][j].first = min(st[i][j - 1].first, st[i + (1 << (j - 1))][j - 1].first);
            st[i][j].second = max(st[i][j - 1].second, st[i + (1 << (j - 1))][j - 1].second);
        }

    //answer queries
    int start, end, currLog, output;
    for (int i = 0; i < queries; i++)
    {
        cin >> start >> end;
        start--;
        end--;
        currLog = log2(end - start + 1);
        output = rangeDif(start, end, currLog);
        cout << output << endl;
    }

    return 0;
}