using pll = pair<long long, long long>;
long long orient(pll p1, pll p2, pll p3)
{
    return (p2.first - p1.first) * (p3.second - p1.second) -
           (p2.second - p1.second) * (p3.first - p1.first);
}
bool inside_tri(pll t1, pll t2, pll t3, pll pt)
{
    return ((orient(t1, t2, pt) < 0) == (orient(t2, t3, pt) < 0)) &&
           ((orient(t2, t3, pt) < 0) == (orient(t3, t1, pt) < 0));
}