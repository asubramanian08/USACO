/*USACO JAN10 Problem 'cheese' Analysis by Tom Conerly

The solution to this problem is dynamic programming. First let’s ignore the crushing aspect of the problem. 
Without crushing the problem is exactly the same as the knapsack problem 
(http://en.wikipedia.org/wiki/Knapsack_problem and 3.2 in USACO training pages). Each type of cheese is one 
possible type item of item we can put in the knapsack. The height of the cheese tower is the total capacity of 
the knapsack. The height of a type of cheese is the amount of space it takes up in the knapsack. Finally the 
value of a type of cheese is the value of having that item in the knapsack. Below if a brief description of how 
to solve the knapsack problem, if you already know how to solve the knapsack problem you should skip the 
explanation. Solving the knapsack problem is done with dynamic programming. Let H be an array of integers giving 
the height of each type of cheese. Let V be an array of integers giving the value of each type of cheese. Let N 
be the number of different types of cheese. The following function returns the maximum value of a knapsack of the 
given size.

int value(int height)
{
    int ans = 0;
    for(int i = 0; i < N; i++) {
        //determine the best knapsack we can make using the ith item next if(H[i] > height)
        continue;
        int val = V[i] + value(height-H[i]); if(val > ans)
        {
            ans = val; 
        }
    }
    return ans; 
}

The code works by attempting to use each of the different types of cheese and then computes the best value that 
can be gained by using that type of cheese. It takes the best value overall all types of cheese and returns it. 
There is a problem with this code, it takes a very long time to run. For a simple analysis consider the case when 
there are two types of cheese, both of height one (this case is trivial to solve, but makes the analysis simple). 
If you call value(5) then there will be two calls to value(4), four calls to value(4), eight calls to value(3) 
and so on. Thus if we call value(X) there will be 2^X total calls to value. For this problem the total height was 
at most 1000 so this solution could take 2^1000 which is much too long. The key insight here is that value(X) 
returns the same value every time that you call it assuming that X is the same. This means that we can save the 
answer from a call to value and simply return that instead of computing it every single time. Let DP be an array 
of integers that stores these computed values. At the start of the program DP will be filled with -1 to indicate 
that none of the values have been computed. 
Here is the code:

int value(int height)
{
    //check if the value has already been computed 
    //if it has, simply return it
    if(DP[height] != -1)
        return DP[height];
    int ans = 0;
    for(int i = 0; i < N; i++) {
        if(H[i] > height)
            continue;
        int val = V[i] + value(height-H[i]);
        if(val > ans)
        {
            ans = val; 
        }
    }
    //save the answer to our table DP[height] = ans;
    return ans;
}

Now lets analyze how long it takes for this code to run. Lets assume that there are N items, and the total height 
is T. The for loop only runs once for each different parameter given to value. There are T different values for 
height so the for loop runs O(T) times. The for loop goes over N elements so it costs O(N). So the total runtime 
is O(TN). For our problem N = 100 and T = 1000 so TN is 10^5 which is easily under the time limit. This is just 
one explanation of the knapsack problem, I found the best way to understand dynamic programming problems is to 
read multiple explanations of them. Now that we can solve the knapsack problem lets reintroduce the crushing 
aspect of this problem. First notice that if we put a "large" piece of cheese into the tower we are always best 
off putting it at the top of the tower so that it crushes everything below it. So one solution is to try having 
each "large" piece of cheese at the top of the tower, then checking how much value we can get from the rest of 
the tower. The rest of the tower is crushed so finding the value of the rest of the tower is just the knapsack 
problem with heights 4/5ths of their old value. We must also check the best tower we can make using only small 
objects. 

Here is the code: */
#include <cstdio>
#include <algorithm>
using namespace std;
FILE *fin = freopen("cheese.in", "r", stdin);
FILE *fout = freopen("cheese.out", "w", stdout);
int v[100], h[100];
int dp_normal[1001], dp_crush[1001];
int n, t, k;
//solve knapsack without crushing
int normal(int height)
{
    if (dp_normal[height] != -1)
        return dp_normal[height];
    int ans = 0;
    for (int i = 0; i < n; i++)
    {
        if (h[i] > height)
            continue;
        int val = v[i] + normal(height - h[i]);
        if (val > ans)
            ans = val;
    }
    dp_normal[height] = ans;
    return ans;
}
//solve knapsack assuming all items are crushed
//same as normal except items are 4/5ths their old height
int crush(int height)
{
    if (dp_crush[height] != -1)
        return dp_crush[height];
    int ans = 0;
    for (int i = 0; i < n; i++)
    {
        int item_height = h[i] * 4 / 5;
        if (item_height > height)
            continue;
        int val = v[i] + crush(height - item_height);
        if (val > ans)
            ans = val;
    }
    dp_crush[height] = ans;
    return ans;
}
int main()
{
    scanf("%d %d %d", &n, &t, &k);
    for (int i = 0; i < n; i++)
        scanf("%d %d", &v[i], &h[i]);
    for (int i = 0; i <= 1000; i++)
    {
        dp_normal[i] = -1;
        dp_crush[i] = -1;
    }
    int best = normal(t);
    for (int i = 0; i < n; i++)
    {
        if (h[i] >= k)
        {
            best = max(best, crush(t - h[i]) + v[i]);
        }
    }
    printf("%d\n", best);
}