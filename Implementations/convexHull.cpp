//starleague week 11 q4

int orient(point &p1, point &p2, point &p3)
{
    ll val = (ll)(p2.y - p1.y) * (ll)(p3.x - p2.x) -
             (ll)(p2.x - p1.x) * (ll)(p3.y - p2.y);

    if (val == 0)
        return 0;
    return (val > 0) ? -1 : 1;
}
bool cmpAng(point &p1, point &p2)
{
    int o = orient(p0, p1, p2);
    if (o == 0)
        return sqr_dist(p0, p1) < sqr_dist(p0, p2);
    return o > 0;
}
vector<point> convexHull(int numPoints, point *points)
{
    //sort array (by the angle from the smallest yPoint)
    int minPt = 0;
    for (int i = 0; i < numPoints; i++)
        if (points[i].y < points[minPt].y ||
            (points[i].y == points[minPt].y &&
             points[i].x < points[minPt].x))
            minPt = i;
    swapPt(points[0], points[minPt]);
    p0 = points[0];
    sort(&points[1], &points[numPoints], cmpAng);

    //find the hull (stack)
    stack<int> hull;
    hull.push(0);
    hull.push(1);
    int p1, p2, p3; //from closest to start
    for (int i = 2; i < numPoints; i++)
    {
        do
        {
            //find the 3 points
            p3 = i;
            p2 = hull.top();
            hull.pop();
            p1 = hull.top();
            //check
        } while ((hull.size() > 1) && (orient(points[p1], points[p2], points[p3]) <= 0));
        hull.push(p2);
        hull.push(p3);
    }

    //return (vector from stack)
    vector<point> hullVtr;
    while (hull.size() != 0)
    {
        hullVtr.push_back(points[hull.top()]);
        hull.pop();
    }
    reverse(hullVtr.begin(), hullVtr.end());
    return hullVtr;
}