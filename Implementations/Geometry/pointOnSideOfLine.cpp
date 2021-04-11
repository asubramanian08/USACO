int side(point &pt, line &ln)
{
    if (orient(ln.first, ln.second, pt) == 0)
        return 0; //on line
    //side true - up, false- down
    point upPt = mp(ln.first.x, ln.first.y + 1);
    bool side = orient(ln.first, ln.second, pt) == orient(ln.first, ln.second, upPt);
    return side ? 1 : -1;
}