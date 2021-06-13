#include <iostream>
#include <algorithm>
#include <complex>
#include <cmath>
using namespace std;

#define epsilon .001
typedef complex<double> cpx;
typedef pair<double, double> point;
#define x first
#define y second
typedef pair<point, point> line;
#define mp make_pair

bool operator==(const point &p1, const point &p2)
{
    return (abs(p1.x - p2.x) < epsilon) && (abs(p1.y - p2.y) < epsilon);
}
bool operator!=(const point &p1, const point &p2)
{
    return !(p1 == p2);
}
point sym_pal(point &P, line ln)
{
    cpx p(P.x, P.y);
    cpx a(ln.first.x, ln.first.y);
    cpx b(ln.second.x, ln.second.y);
    cpx pt = p - a;
    cpx bt = b - a;
    cpx pr = pt / bt;
    cpx ret = conj(pr) * bt + a;
    return mp(ret.real(), ret.imag());
}
line perpBi(line opLine)
{
    line corrLn;
    corrLn.first.x = (opLine.first.x + opLine.second.x) / 2;
    corrLn.first.y = (opLine.first.y + opLine.second.y) / 2;
    corrLn.second.x = corrLn.first.x + (opLine.first.y - opLine.second.y);
    corrLn.second.y = corrLn.first.y - (opLine.first.x - opLine.second.x);
    return corrLn;
}
void handleDoub(double &urMum)
{
    if (abs((int)urMum - urMum) < epsilon)
        urMum = (int)urMum;
    else if (abs((int)(urMum + 0.5) - urMum) < epsilon)
        urMum = (int)(urMum + 0.5);
    else if (abs((int)(urMum - 0.5) - urMum) < epsilon)
        urMum = (int)(urMum - 0.5);
}
bool is_symLine(line corrLn, point *points, int numPoints)
{
    point otherPt;
    int potPos;
    for (int i = 0; i < numPoints; i++)
    {
        otherPt = sym_pal(points[i], corrLn);
        handleDoub(otherPt.x);
        handleDoub(otherPt.y);
        potPos = lower_bound(&points[0], &points[numPoints], otherPt) - &points[0];
        if (otherPt != points[potPos])
            return false;
    }
    return true;
}

int main(void)
{
    //read
    FILE *junk;
    junk = freopen("symmetry.in", "r", stdin);
    junk = freopen("symmetry.out", "w", stdout);
    int numPoints;
    cin >> numPoints;
    point *points = new point[numPoints];
    for (int i = 0; i < numPoints; i++)
        cin >> points[i].first >> points[i].second;

    //find pependicular bisector symmetry lines
    sort(&points[0], &points[numPoints]);
    int symLines = 0;
    for (int i = 1; i < numPoints; i++)
        symLines += is_symLine(perpBi(mp(points[0], points[i])), points, numPoints);

    //if symmetry line goes through points[0]
    line opLine;
    opLine.first = points[1];
    for (int i = 2; i < numPoints; i++)
    {
        opLine.second = points[i];
        if (sym_pal(points[0], perpBi(opLine)) != points[0])
            continue;
        symLines += is_symLine(perpBi(opLine), points, numPoints);
        //break;
    }

    //points[0] and points[1] is a line
    symLines += is_symLine(mp(points[0], points[1]), points, numPoints);

    //delete and print
    delete[] points;
    cout << symLines;
    return 0;
}