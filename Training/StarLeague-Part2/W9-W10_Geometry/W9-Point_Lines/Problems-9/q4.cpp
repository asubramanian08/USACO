#include <iostream>
using namespace std;
typedef pair<int, int> point;
typedef pair<point, point> line;
line *lines;

int cmpLine(const void *p1, const void *p2)
{
    line *l1 = (line *)p1;
    line *l2 = (line *)p2;
    int det1, det2;
    det1 = l1->first.first * l1->second.second - l1->first.second * l1->second.first;
    det2 = l2->first.first * l2->second.second - l2->first.second * l2->second.first;
    return det1 - det2;
}
int side(point pt, int ln)
{
    return (pt.first - lines[ln].first.first) * (lines[ln].second.second - lines[ln].first.second) -
           (pt.second - lines[ln].first.second) * (lines[ln].second.first - lines[ln].first.first);
}
int sign(int num)
{
    if (num < 0)
        return -1;
    if (num == 0)
        return 0;
    return 1;
}

int main(void)
{
    //read input
    /*FILE *junk;
    junk = freopen("regions.in", "r", stdin);
    junk = freopen("regions.out", "w", stdout);*/
    point start, end;
    cin >> start.first >> start.second >> end.first >> end.second;
    int numLines;
    cin >> numLines;
    lines = new line[numLines];
    for (int i = 0; i < numLines; i++)
        cin >> lines[i].first.first >> lines[i].first.second >>
            lines[i].second.first >> lines[i].second.second;

    qsort(lines, numLines, sizeof(line), cmpLine);

    //find ans and print
    int count = 0;
    for (int i = 0; i < numLines; i++)
        if (-1 * sign(side(start, i)) == sign(side(end, i))) //so 0 doesn't work
            if ((i == 0) || (side(lines[i].first, i - 1) != 0) || (side(lines[i].second, i - 1) != 0))
                count++;
    cout << count;
    return 0;
}