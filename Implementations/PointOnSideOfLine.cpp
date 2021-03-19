//look at star league week 9 q4
#include <algorithm>
using namespace std;
typedef pair<int, int> point;
typedef pair<point, point> line;
line *lines;

int side(point pt, int ln)
{
    return (pt.first - lines[ln].first.first) * (lines[ln].second.second - lines[ln].first.second) -
           (pt.second - lines[ln].first.second) * (lines[ln].second.first - lines[ln].first.first);
}