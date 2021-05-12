// Doing to stop debug time -> submit once
// Start: 8:37
// Think: 9:00
// Write: 9:15
#include <iostream>
#include <algorithm>
using namespace std;

int dir(char ch)
{
    switch (ch)
    {
    case 'N':
        return 0;
    case 'E':
        return 1;
    case 'S':
        return 2;
    case 'W':
        return 3;
    }
    return 0; // for the warning
}
//-1 for left +1 for right
int turn(char from, char to)
{
    int f = dir(from), t = dir(to);
    if (f == t)
        return 0; // straight
    if ((f + 1) % 4 == t)
        return 1; //right
    return -1;    //left
}

int main(void)
{
    //read
    int queries, overall;
    char ch, start, last;
    cin >> queries;
    cin.get(ch); // new line
    for (int i = 0; i < queries; i++)
    {
        overall = 0;
        cin.get(start);
        cin.get(ch);
        for (last = start; ch != '\n'; last = ch, cin.get(ch))
            overall += turn(last, ch);
        overall += turn(last, start);
        if (overall < 0)
            cout << 'C';
        cout << "CW\n";
    }
    return 0;
}