/*USACO FEB13 Problem 'perimeter' Analysis by Fatih Gelgi and Brian Dean

This problem can be solved by simulating the tour around the bales. Consider the example given in the 
problem (including the borders of the cells):

.-.-.
|X|X|
.-.-.-.-.
|X| |X|X|
.- - -.-.
|X|X|X|
.-.-.-.

We just need to walk on the outer border of the cells of the hay bales. Walking outside the border can be 
accomplished by right hand rule: keep your right hand on the wall when walking. Try to turn right first. 
If not available use the current direction. If current direction is also not available then turn left.

    S
    |X X
v-<-<
|X X

In the figure above, S is the starting location and the direction is south. Move one step to south then we 
can turn to right. But in the next step, we cannot turn right hence continue walking one more step. Now we 
cannot turn right or continue walking in the same direction. So we have to run left this time and so on. 
At the end of the walk, we come back to the starting location. First we should determine a starting 
location and the direction. Top leftmost corner is a reasonable place to start (shown with 'S' in the 
following figure) and the direction can be either south or east -- suppose we choose south.

S-<-<
|X X|
v   ^-<-<
|X   X X|
v     >-^
|X X X| 
>->->-^

To implement the idea we cannot use a matrix; it will not fit in the memory hence we only need to keep the 
bale locations. We can use STL map / set in C++ or HashSet / Hashtable in Java. Here, there is a nice 
trick with STL map, we sightly change our matrix description int mat and use the same code in the Bronze 
version of the problem:

map<int,map<int,int> > mat;
In the problem (1,1) is the lower-left cell. Actually, it doesn't matter; we can use matrix (row,column) 
as the cell locations. In this case, the shape will be flipped but the perimeter will be same. In this 
setting, notice that our walking coordinates are different than matrix cell locations. We consider (1,1) 
is the top-left corner of the cell

(1,1) and its bottom-right corner is (2,2).

(1,1).-.(1,2)
     |X|
     .-.
(2,1)   (2,2)

Hence, to check if south direction of (y,x) is available when walking, mat[y][x] must contain a bale. 
Similarly, mat[y-1][x-1] has to be occupied for north, mat[y-1][x] for east and mat[y][x-1] for west.

Since we make O(N) lookups in the matrix implemented with map, the complexity will be O(N log N). It is not 
necessary for the problem but one can improve the complexity to O(N) using STL unordered_map in C++ or 
Hashtable in Java.

Here's a sample solution: */

#include <fstream>
#include <map>
#define MAX 1000000
using namespace std;
// directions: down,right,up,left
const int dir[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};
map<int, map<int, int>> mat;
int perimeter, sy = MAX, sx = MAX, d;
int main()
{

    ifstream fin("perimeter.in");
    int n, x, y;
    fin >> n;
    for (int i = 0; i < n; i++)
    {
        fin >> x >> y;
        mat[y][x] = 1;
        // update starting postion
        // the upper-leftmost corner of the shape
        if (y < sy || (y == sy && x < sx))
            sy = y, sx = x;
    }
    fin.close();
    // walk around the bales using right hand rule
    y = sy, x = sx;
    do
    {
        // update coordinates with respect to the direction
        y += dir[d][0], x += dir[d][1], perimeter++;
        // determine new direction
        // start from previous direction to search
        for (d = (d + 3) % 4;; d = (d + 1) % 4)
            // check neighbor bale locations based on direction
            if ((d == 0 && mat[y][x]) || (d == 1 && mat[y - 1][x]) || (d == 2 && mat[y - 1][x - 1]) || (d == 3 && mat[y][x - 1]))
                break;
    }
    // continue until coming back to the starting location
    while (y != sy || x != sx);
    ofstream fout("perimeter.out");
    fout << perimeter << endl;
    fout.close();
}