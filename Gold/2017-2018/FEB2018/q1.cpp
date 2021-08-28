// Start: 10:00
// Think: 10:27,12:30-1:04
// Write: 1:32
// Debug: 1:35
#include <iostream>
#include <set>
#include <map>
#include <vector>
using namespace std;

using pii = pair<int, int>;

int main(void)
{
    //read
#ifndef HOME
    freopen("snowboots.in", "r", stdin);
    freopen("snowboots.out", "w", stdout);
#endif
    int numTiles, numBoots;
    cin >> numTiles >> numBoots;
    int *tiles = new int[numTiles];
    for (int i = 0; i < numTiles; i++)
        cin >> tiles[i];

    //get list of pile locs
    set<int> heights;
    map<int, vector<int>> listLocs;
    for (int i = 1; i < numTiles - 1; i++)
        if (heights.find(tiles[i]) != heights.end())
            listLocs[tiles[i]].push_back(i);
        else
        {
            heights.insert(tiles[i]);
            listLocs[tiles[i]] = vector<int>({i});
        }

    //remove tile heights, get max dist
    set<pii> minJump;
    pii *dist = new pii[numTiles];
    for (int i = 0; i < numTiles; i++)
        dist[i].first = dist[i].second = 1;
    int maxDist = 1;
    while (!heights.empty())
    {
        int currHeight = *heights.rbegin();
        heights.erase(currHeight);
        for (int ele : listLocs[currHeight])
        {
            maxDist = max(maxDist, dist[ele].first + dist[ele].second);
            dist[ele - dist[ele].first].second += dist[ele].second;
            dist[ele + dist[ele].second].first += dist[ele].first;
        }
        minJump.insert({currHeight - 1, maxDist});
    }

    //answer queries
    int depth, step;
    for (int i = 0; i < numBoots; i++)
    {
        cin >> depth >> step;
        auto pos = minJump.lower_bound({depth, 0});
        if (pos == minJump.end() || step >= pos->second)
            cout << '1' << endl;
        else
            cout << '0' << endl;
    }

    //delete
    delete[] tiles;
    delete[] dist;
    return 0;
}