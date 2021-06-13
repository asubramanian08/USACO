#include <iostream>
#include <vector>
using namespace std;

#define MOD 1000000007
#define NUM_PAINT 3
struct barn
{
    int paint;
    //0 = not paint, anything is paint[num]
    long long ways[NUM_PAINT];
    vector<int> conns;
};
barn *barns;
void findCombonations(int currBarn, int parent)
{
    //finish the childrens combonations
    for (int i = 0; i < barns[currBarn].conns.size(); i++)
        if (barns[currBarn].conns[i] != parent)
            findCombonations(barns[currBarn].conns[i], currBarn);

    //initialize the ways
    if (barns[currBarn].paint == 0)
        for (int i = 0; i < NUM_PAINT; i++)
            barns[currBarn].ways[i] = 1;
    else
    {
        for (int i = 0; i < NUM_PAINT; i++)
            barns[currBarn].ways[i] = 0;
        barns[currBarn].ways[barns[currBarn].paint - 1] = 1;
    }

    //finish finding ways (multiply)
    for (int i = 0; i < barns[currBarn].conns.size(); i++)
        if (barns[currBarn].conns[i] != parent)
            for (int colorPick = 0; colorPick < NUM_PAINT; colorPick++)
            {
                long long mult = 0;
                for (int j = 1; j < NUM_PAINT; j++)
                    mult += barns[barns[currBarn].conns[i]].ways[(colorPick + j) % NUM_PAINT];
                barns[currBarn].ways[colorPick] *= mult;
                barns[currBarn].ways[colorPick] %= MOD;
            }
}

int main(void)
{
    /*FILE *junk;
    junk = freopen("barnpainting.in", "r", stdin);
    junk = freopen("barnpainting.out", "w", stdout);*/
    //get tree
    int numBarns, numPainted;
    cin >> numBarns >> numPainted;
    barns = new barn[numBarns];
    for (int i = 0; i < numBarns; i++)
        barns[i].paint = 0;
    int b1, b2;
    for (int i = 1; i < numBarns; i++)
    {
        cin >> b1 >> b2;
        b1--;
        b2--;
        barns[b1].conns.push_back(b2);
        barns[b2].conns.push_back(b1);
    }
    for (int i = 0; i < numPainted; i++)
    {
        cin >> b1 >> b2; //b1 = barn, b2 = paint
        b1--;
        barns[b1].paint = b2;
    }

    //find combonations
    findCombonations(0, -1); //pick 0 as root
    long long ans = 0;
    for (int i = 0; i < NUM_PAINT; i++)
    {
        ans += barns[0].ways[i];
        ans %= MOD;
    }
    cout << ans;
    return 0;
}