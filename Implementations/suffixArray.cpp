#define MAX_LEN 100000
#define MAX_LOG 17
#define mp make_pair
using pii = pair<int, int>;
#define NA -1
int logInt2(int num)
{
    int ans = 1;
    while ((num >>= 1) != 0)
        ans++;
    return ans;
}
int suffixArray[MAX_LOG][MAX_LEN];
int initSuffixArray(const string &str)
{
    int lg = logInt2(str.size());
    pair<pii, int> *location = new pair<pii, int>[str.size()];
    for (int i = 0; i < str.size(); i++)
        suffixArray[0][i] = str[i] - 'a';
    for (int i = 1, dist = 1; i < lg; i++, dist *= 2)
    {
        for (int j = 0; j < str.size(); j++)
        {
            location[j].first.first = suffixArray[i - 1][j];
            location[j].first.second = j + dist < str.size() ? suffixArray[i - 1][j + dist] : NA;
            location[j].second = j;
        }
        sort(location, location + str.size());
        for (int j = 0, pos = 0; j < str.size(); j++)
        {
            pos += (j != 0) && (location[j].first != location[j - 1].first);
            suffixArray[i][location[j].second] = pos;
        }
    }
    delete[] location;
    return lg - 1;
}