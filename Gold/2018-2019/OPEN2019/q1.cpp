// Start: 7:30
// Think: 7:44
// Write: 8:03
// Debug: 8:06
#include <iostream>
using namespace std;

#define MAX_GROUP 410
long long DP[MAX_GROUP][MAX_GROUP];
#define BIG_NUM 10000000000

int main(void)
{
    //read
#ifndef HOME
    freopen("snakes.in", "r", stdin);
    freopen("snakes.out", "w", stdout);
#endif
    int numSnakes, nets;
    cin >> numSnakes >> nets;
    int *snakes = new int[numSnakes];
    for (int i = 0; i < numSnakes; i++)
        cin >> snakes[i];
    nets++;

    //init DP end
    for (int i = 0; i <= nets; i++)
        DP[numSnakes][i] = 0;

    //run the DP: n^3
    for (int i = numSnakes - 1; i >= 0; i--)
        for (int j = 0; j <= nets; j++)
        {
            DP[i][j] = BIG_NUM;
            if (j == 0)
                continue;
            int largest = snakes[i], cost = 0;
            for (int k = i + 1; k <= numSnakes; k++)
            {
                DP[i][j] = min(DP[i][j], cost + DP[k][j - 1]);
                if (snakes[k] > largest)
                {
                    cost += (k - i) * (snakes[k] - largest);
                    largest = snakes[k];
                }
                cost += largest - snakes[k];
            }
        }

    //print and delete
    cout << DP[0][nets] << endl;
    delete[] snakes;
    return 0;
}