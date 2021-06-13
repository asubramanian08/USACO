/*USACO OPEN13 Problem 'haywire' Analysis by Jonathan Paulson and Brian Dean

The obvious first thought is to try all 12! possible orderings of the cows, and return the one with the 
minimum cost. But this is about 12!*12*3/2=9 billion operations, so it is too slow. This method can only 
solve cases with N <= 10.

For N = 12, this problem was (as intended!) a bit more challenging to solve in time. There are a few 
approaches one can use to accomplish this. First, we can recursively generate all 12! orderings, but we 
can be clever as we go and "prune" our search any time we realize that our current partial solution will 
never end up better than the best complete solution found so far.

In the code below, we recursively build up all 12! orderings. The variables cows_so_far and cost_so_far 
tell us the number of cows and the cost of the links between these cows in the partial solution built so 
far. The pending_links variable tells us the number of links that have started in our partial solution but 
not yet terminated (so these links will go to cows we have not yet added); pending_link_cost tells us the 
sum of lengths so far of all these links. Observe that pending_link_cost is a lower bound on the cost of 
completing our solution, so if we ever reach a point where this cost plus the cost of the completed links 
in our partial solution is larger than the cost of the best solution found so far, we can immediately 
prune the search, back up, and try other possibilities. As a result, we end up streamlining our search and 
generating far fewer than all possible 12! orderings.*/

#include <iostream>
#include <fstream>
#include <algorithm>
using namespace std;
int N;
int nbr[13][3];
int best = 9999999, cow_pos[13];
void solve(int cows_so_far, int cost_so_far, int pending_links, int pending_link_cost)
{
    if (cows_so_far == N)
    {
        best = min(best, cost_so_far);
        return;
    }
    /* Prune search if no hope of beating the best solution found so far... */ if (cost_so_far + pending_link_cost >= best)
        return;
    cows_so_far++;
    for (int i = 1; i <= N; i++)
        if (cow_pos[i] == 0)
        {
            cow_pos[i] = cows_so_far;
            int added_cost = 0, new_pending_links = 3;
            for (int j = 0; j < 3; j++)
                if (cow_pos[nbr[i][j]] != 0)
                {
                    added_cost += cow_pos[i] - cow_pos[nbr[i][j]];
                    new_pending_links -= 2;
                }
            solve(cows_so_far,
                  cost_so_far + added_cost,
                  pending_links + new_pending_links,
                  pending_link_cost + (pending_links + new_pending_links) - added_cost);
            cow_pos[i] = 0;
        }
}
int main(void)
{
    ifstream fin("haywire.in");
    ofstream fout("haywire.out");
    fin >> N;
    for (int i = 1; i <= N; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            fin >> nbr[i][j];
        }
    }
    solve(0, 0, 0, 0);
    fout << best << "\n";
    return 0;
}