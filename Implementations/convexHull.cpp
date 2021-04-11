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