/*USACO JAN08 Problem 'alake' Analysis by Neal Wu and Richard Peng

We try to solve the problem for each level separately. For each level, the amount of water required until 
it overflows can be broken down into three parts. WOLOG, we assume the level is to the left of the level 
of minimum height. The three parts are:

 To the left of the level. Water will flow this way until it encounters the first level that has a higher
height. So, for each level, we need to find the first level to its left that has a higher height. This can 
be done using a stack in O(n) time.

 Between the level and the lowest level. The water levels forms a series of 'steps', which can be tracked 
in a stack if we consider the levels from right to left. This can also be calculated in O(n) time.

 To the right of the lowest level. If we consider the levels one by one leftwards starting from the one 
to the left of the lowest level, the water level at the lowest level can only increase. So it suffices to 
keep a pointer to how far to the right gets submerged and increase this counter as we go. This clearly 
also runs in O(n)

Combining these three parts, we get an O(n) algorithm. Many of the solutions submitted by contestants used 
much cleverer algorithms that combines these three steps into a single one, but most are still based on 
this 'step' idea. Here is Neal Wu's explanation on how he did this problem:

Add in the two infinite barriers as 'levels' with infinite height for simplicity. We will find the answer 
for each level in the order they are filled, keeping track of the current time when calculating each.

Note that after we have filled level L, the water will go in the direction of the shorter neighbor level 
of L. For example, in the following diagram, after level 2 is filled, the water will flow to the right:

*             * 8
*             * 7
****          * 6
****  **      * 5 <-- heights 
****  ****    * 4
****  ******* * 3
****  ********* 2
*************** 1
 1  2 3 4 5  6
    Levels

The water will keep flowing to the right (and thus 'skipping' levels) until an increase in height occurs. 
Thus, in the example above, level 6 will be filled next after level 2 is finished.

Also, note that at this point both level 2 and level 3 share the same water level. They will always remain 
at the same height since the water fills them evenly. Thus, we can 'merge' level 2 into level 3 (the new 
width of level 3 will be the sum of its original width and the width of level 2), and delete level 2. Note 
that to implement this merging efficiently we can use a linked list of levels (which enables constant time 
deletion of a level).

This gives us a fairly simple algorithm: find the level which the water currently fills (starting with the 
shortest level), and calculate the time at which it becomes submerged (which is equal to the time when the 
level began to fill up added to the width of the level). Next, find how long it takes for the level to fill 
up to the height of the shorter of its two neighbors, and add this to our current time. Finally, continue 
in the direction of the shorter neighbor until we reach an increase in level heights. This level is the 
next level to fill with water.

At first, it seems this approach is O(N2), since we can skip up to O(N) levels each time. However, the 
algorithm is actually linear time because of the following fact: after we skip a level, we cannot skip it 
again. This is because after a level is skipped, the water must come back to it from the opposite 
direction, which means it must fill the level. (In the above example, the water will skip level 5, fill 
level 6, and then come back to level 5 and fill it.) Therefore each level can be skipped at most once, so 
the algorithm takes O(N) time overall. The following is a sample implementation:*/

#include <cstdio>
using namespace std;
FILE *fin = fopen("alake.in", "r");
FILE *fout = fopen("alake.out", "w");
const int MAXN = 100005, INF = 1000000000;
int N, width[MAXN], height[MAXN];
int prev[MAXN], next[MAXN]; // simplified linked list long long ans [MAXN], total = 0;
long long ans[MAXN], total = 0;

int main()
{
    fscanf(fin, "%d", &N);
    height[0] = height[N + 1] = INF; // infinite walls
    int ind = 1;                     // the current level being filled with water
    for (int i = 1; i <= N; i++)
    {
        fscanf(fin, "%d %d", width + i, height + i);
        prev[i] = i - 1, next[i] = i + 1; //initialize
        if (height[i] < height[ind])      // ind starts as the shortest level
            ind = i;
    }
    // continue until the current level is one of the walls
    while (height[ind] < INF)
    {
        ans[ind] = total + width[ind]; // calculate our current index
        // delete the current index
        next[prev[ind]] = next[ind], prev[next[ind]] = prev[ind];
        // take the smaller of the neighbors
        if (height[prev[ind]] < height[next[ind]])
        {
            // add the time taken to our current total
            total += (long long)width[ind] * (height[prev[ind]] - height[ind]);
            width[prev[ind]] += width[ind]; // merge the levels together
            ind = prev[ind];
            while (ind > 0 && height[prev[ind]] < height[ind]) // find the next index
                ind = prev[ind];
        }
        else
        { // do similarly for the other neighbor
            total += (long long)width[ind] * (height[next[ind]] - height[ind]);
            width[next[ind]] += width[ind];
            ind = next[ind];
            while (ind <= N && height[next[ind]] < height[ind])
                ind = next[ind];
        }
    }
    for (int i = 1; i <= N; i++)
        fprintf(fout, "%lld\n", ans[i]);
    return 0;
}