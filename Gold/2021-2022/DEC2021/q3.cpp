#include <iostream>
#include <vector>
using namespace std;

#define NA -1
#define MAX_SIZE 50

int main(void)
{
    // read
    int tests, colors, sweeps, lines, color;
    cin >> tests;
    using pii = pair<int, int>;
    pii pos[MAX_SIZE][MAX_SIZE];
    for (int run = 0; run < tests; run++)
    {
        bool works = true;
        cin >> colors >> sweeps;
        pii *cover = new pii[colors];
        for (int i = 0; i < colors; i++)
            cover[i] = pii(NA, NA);
        for (int i = 0; i < sweeps; i++)
        {
            for (int j = 0; j < colors; j++)
                pos[i][j] = pii(NA, NA);
            cin >> lines;
            for (int j = 0; j < lines; j++)
            {
                cin >> color;
                color--;
                if (cover[color].second != NA && cover[color].second < i - 1)
                    works = false;
                cover[color].second = i;
                if (cover[color].first == NA)
                    cover[color].first = i;
                (pos[i][color].first == NA ? pos[i][color].first : pos[i][color].second) = j;
            }
        }

        // inter-color
        auto getType = [](pii p1, pii p2)
        {
            vector<int> ct(2);
            if (p1.first <= p2.first)
                ct[0] = 0 + (p1.first == p2.first ? 3 : 0);
            else if (p1.first <= p2.second)
                ct[0] = 1 + (p1.first == p2.second ? 3 : 0);
            else
                ct[0] = 2;
            if (p1.second <= p2.first)
                ct[1] = 0 + (p1.second == p2.first ? 3 : 0);
            else if (p1.second <= p2.second)
                ct[1] = 1 + (p1.second == p2.second ? 3 : 0);
            else
                ct[1] = 2;
            return ct;
        };
        for (int i = 0; i < colors && works; i++)
            for (int j = i + 1; j < colors && works; j++)
            {
                // check for crosses
                vector<int> type, ct(2);
                for (int line = max(cover[i].first, cover[j].first);
                     line <= min(cover[i].second, cover[j].second) && works; line++)
                {
                    ct = getType(pos[line][i], pos[line][j]);
                    if (type.empty())
                        type = {ct[0], ct[1]};
                    else
                        works = (type[0] == ct[0] && type[1] == ct[1]);
                    if ((ct[1] == 2 && ct[0] == 1) || (ct[1] == 1 && ct[0] == 0))
                        works = false;
                }
                // endings
                type = getType(cover[i], cover[j]);
                if ((type[1] == 2 && type[0] == 1) || (type[1] == 1 && type[0] == 0))
                    works = false;
            }

        // print and delete
        if (works)
            cout << "YES" << endl;
        else
            cout << "NO" << endl;
        delete[] cover;
    }
    return 0;
}