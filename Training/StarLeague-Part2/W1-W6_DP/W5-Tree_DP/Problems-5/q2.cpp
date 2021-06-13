#include <iostream>
#include <vector>
using namespace std;

#define BIG_NUM 10000000
struct node
{
    vector<int> conns;
    bool state;
    int cost[2][2];
    //cost[tog][on] = cost[1][1]
};
node *lights;
void calcNode(int pos, int parent)
{
    for (int i = 0; i < lights[pos].conns.size(); i++)
        if (lights[pos].conns[i] != parent)
            calcNode(lights[pos].conns[i], pos);

    lights[pos].cost[0][lights[pos].state] = 0;
    lights[pos].cost[1][lights[pos].state] = BIG_NUM;
    lights[pos].cost[0][!lights[pos].state] = BIG_NUM;
    lights[pos].cost[1][!lights[pos].state] = 1;

    int temp1, temp2;
    for (int i = 0; i < lights[pos].conns.size(); i++)
        if (lights[pos].conns[i] != parent)
        {
            temp1 = lights[pos].cost[0][lights[pos].state];
            temp2 = lights[pos].cost[0][!lights[pos].state];

            lights[pos].cost[0][lights[pos].state] = BIG_NUM;
            if ((temp1 != BIG_NUM) && (lights[lights[pos].conns[i]].cost[0][1] != BIG_NUM))
                lights[pos].cost[0][lights[pos].state] =
                    min(lights[pos].cost[0][lights[pos].state],
                        temp1 + lights[lights[pos].conns[i]].cost[0][1]);
            if ((temp2 != BIG_NUM) && (lights[lights[pos].conns[i]].cost[1][1] != BIG_NUM))
                lights[pos].cost[0][lights[pos].state] =
                    min(lights[pos].cost[0][lights[pos].state],
                        temp2 + lights[lights[pos].conns[i]].cost[1][1]);

            lights[pos].cost[0][!lights[pos].state] = BIG_NUM;
            if ((temp2 != BIG_NUM) && (lights[lights[pos].conns[i]].cost[0][1] != BIG_NUM))
                lights[pos].cost[0][!lights[pos].state] =
                    min(lights[pos].cost[0][!lights[pos].state],
                        temp2 + lights[lights[pos].conns[i]].cost[0][1]);
            if ((temp1 != BIG_NUM) && (lights[lights[pos].conns[i]].cost[1][1] != BIG_NUM))
                lights[pos].cost[0][!lights[pos].state] =
                    min(lights[pos].cost[0][!lights[pos].state],
                        temp1 + lights[lights[pos].conns[i]].cost[1][1]);

            temp1 = lights[pos].cost[1][lights[pos].state];
            temp2 = lights[pos].cost[1][!lights[pos].state];

            lights[pos].cost[1][lights[pos].state] = BIG_NUM;
            if ((temp1 != BIG_NUM) && (lights[lights[pos].conns[i]].cost[0][0] != BIG_NUM))
                lights[pos].cost[1][lights[pos].state] =
                    min(lights[pos].cost[1][lights[pos].state],
                        temp1 + lights[lights[pos].conns[i]].cost[0][0]);
            if ((temp2 != BIG_NUM) && (lights[lights[pos].conns[i]].cost[1][0] != BIG_NUM))
                lights[pos].cost[1][lights[pos].state] =
                    min(lights[pos].cost[1][lights[pos].state],
                        temp2 + lights[lights[pos].conns[i]].cost[1][0]);

            lights[pos].cost[1][!lights[pos].state] = BIG_NUM;
            if ((temp2 != BIG_NUM) && (lights[lights[pos].conns[i]].cost[0][0] != BIG_NUM))
                lights[pos].cost[1][!lights[pos].state] =
                    min(lights[pos].cost[1][!lights[pos].state],
                        temp2 + lights[lights[pos].conns[i]].cost[0][0]);
            if ((temp1 != BIG_NUM) && (lights[lights[pos].conns[i]].cost[1][0] != BIG_NUM))
                lights[pos].cost[1][!lights[pos].state] =
                    min(lights[pos].cost[1][!lights[pos].state],
                        temp1 + lights[lights[pos].conns[i]].cost[1][0]);
        }
}
int main(void)
{
    /*FILE *junk;
    junk = freopen("christmas.in", "r", stdin);
    junk = freopen("christmas.out", "w", stdout);*/
    int bulbs;
    cin >> bulbs;
    lights = new node[bulbs];
    for (int i = 0; i < bulbs; i++)
        cin >> lights[i].state;
    int n1, n2;
    for (int i = 1; i < bulbs; i++)
    {
        cin >> n1 >> n2;
        n1--;
        n2--;
        lights[n1].conns.push_back(n2);
        lights[n2].conns.push_back(n1);
    }

    calcNode(0, -1);
    int ans = min(lights[0].cost[0][1], lights[0].cost[1][1]);
    if (ans != BIG_NUM)
        cout << ans;
    else
        cout << "Impossible";
    return 0;
}