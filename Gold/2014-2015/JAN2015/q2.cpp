// Start: 9:55
// Think: 10:09
// Write: 10:37
// Debug: 10:41
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int main(void)
{
    //read
#ifndef HOME
    freopen("movie.in", "r", stdin);
    freopen("movie.out", "w", stdout);
#endif
    int numMovies, hideTime;
    cin >> numMovies >> hideTime;
    int *duration = new int[numMovies];
    vector<int> *listings = new vector<int>[numMovies];
    for (int i = 0; i < numMovies; i++)
    {
        int numListings;
        cin >> duration[i] >> numListings;
        listings[i].resize(numListings);
        for (int j = 0; j < numListings; j++)
            cin >> listings[i][j];
    }

    //DP[mask]: longest time with said mask
    int *DP = new int[1 << numMovies];
    fill(DP, DP + (1 << numMovies), 0);
    for (int mask = 0; mask < (1 << numMovies); mask++)
        for (int i = 0; i < numMovies; i++)
            if ((mask & (1 << i)) == 0 && DP[mask] >= listings[i][0])
                DP[mask | (1 << i)] = max(DP[mask | (1 << i)],
                                          upper_bound(listings[i].begin(),
                                                      listings[i].end(),
                                                      DP[mask])[-1] +
                                              duration[i]);

    //print and delete
    auto movieCount = [numMovies](int mask)
    {
        int count = 0;
        for (int i = 0; i < numMovies; i++)
            if (mask & (1 << i))
                count++;
        return count;
    };
    int leastMovies = numMovies + 1;
    for (int mask = 0; mask < (1 << numMovies); mask++)
        if (DP[mask] >= hideTime)
            leastMovies = min(leastMovies, movieCount(mask));
    if (leastMovies <= numMovies)
        cout << leastMovies << endl;
    else
        cout << -1 << endl;
    delete[] duration;
    delete[] listings;
    delete[] DP;
    return 0;
}