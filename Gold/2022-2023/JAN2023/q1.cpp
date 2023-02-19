// Official: Correct
#include <iostream>
#include <string>
using namespace std;

#define LARGE 1000000000000000000
long long reference[200010][26];
string expand[200010];
char change[200010];
long long range[200010] = {0};
string answer[200010];

string print(long long level, long long left, long long right)
{
    if (answer[level] != "")
        return answer[level].substr(left, right - left);
    long long letterStart, letterEnd = 0;
    string ans;
    for (char ch : expand[level])
    {
        letterStart = letterEnd;
        if (reference[level + 1][ch - 'a'] < 26)
            letterEnd = letterStart + 1;
        else
            letterEnd = letterStart + range[reference[level + 1][ch - 'a'] - 26];
        if (letterEnd <= left)
            continue;
        if (letterStart >= right)
            break;
        if (reference[level + 1][ch - 'a'] < 26)
            ans += ch;
        else
            ans += print(reference[level + 1][ch - 'a'] - 26,
                         max(left - letterStart, 0ll),
                         min(letterEnd, right) - letterStart);
    }
    if (left == 0 && right == range[level])
        answer[level] = ans;
    return ans;
}

int main(void)
{
    ios_base::sync_with_stdio(false);
    long long l, r, n;
    cin >> l >> r >> n;
    for (long long i = 0; i < n; i++)
        cin >> change[i] >> expand[i];
    for (long long i = 0; i < 26; i++)
        reference[n][i] = i;
    for (long long i = n - 1; i >= 0; i--)
    {
        for (long long j = 0; j < 26; j++)
            reference[i][j] = reference[i + 1][j];
        reference[i][change[i] - 'a'] = 26 + i;
    }
    for (long long i = n - 1; i >= 0; i--)
        for (char ch : expand[i])
            if (reference[i + 1][ch - 'a'] < 26)
                range[i]++;
            else if (range[i] > LARGE)
                break;
            else
                range[i] += range[reference[i + 1][ch - 'a'] - 26];
    cout << print(0, l - 1, r) << endl;
    return 0;
}