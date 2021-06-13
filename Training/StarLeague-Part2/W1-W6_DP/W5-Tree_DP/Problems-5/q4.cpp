#include <iostream>
#include <string.h>
using namespace std;
#define BIG_NUM 1000000000000000
struct dir
{
    bool is_file;
    int numCont;
    int *contains;
    long long charsDown;
    int filesInside;
    int nameLen;
};
dir *work_space;
int findRoot(int numDirs)
{
    bool *used = new bool[numDirs];
    memset(used, true, numDirs);
    for (int i = 0; i < numDirs; i++)
        for (int j = 0; j < work_space[i].numCont; j++)
            used[work_space[i].contains[j]] = false;
    for (int i = 0; i < numDirs; i++)
        if (used[i])
            return i;
    return 0; //never happen
}
void finishDirInfo(int currDir)
{
    if (work_space[currDir].is_file)
    {
        work_space[currDir].filesInside = 1;
        work_space[currDir].charsDown = work_space[currDir].nameLen;
        return;
    }
    work_space[currDir].charsDown = 0;
    work_space[currDir].filesInside = 0;
    for (int i = 0; i < work_space[currDir].numCont; i++)
    {
        finishDirInfo(work_space[currDir].contains[i]);
        if (!work_space[work_space[currDir].contains[i]].is_file)
            work_space[currDir].charsDown += work_space[work_space[currDir].contains[i]].charsDown +
                                             ((work_space[work_space[currDir].contains[i]].nameLen + 1) *
                                              work_space[work_space[currDir].contains[i]].filesInside);
        else
            work_space[currDir].charsDown += work_space[work_space[currDir].contains[i]].nameLen;
        work_space[currDir].filesInside += work_space[work_space[currDir].contains[i]].filesInside;
    }
}
int totalFiles;
long long bestLen(int currDir, long long chars)
{
    if (work_space[currDir].is_file)
        return BIG_NUM;
    long long myChars = chars +
                        ((totalFiles - work_space[currDir].filesInside) * 3) -
                        (work_space[currDir].filesInside * (work_space[currDir].nameLen + 1));
    long long best = myChars;
    for (int i = 0; i < work_space[currDir].numCont; i++)
        best = min(best, bestLen(work_space[currDir].contains[i], myChars));
    return best;
}
int main(void)
{
    /*FILE *junk;
    junk = freopen("dirtraverse.in", "r", stdin);
    junk = freopen("dirtraverse.out", "w", stdout);*/
    int numDirs;
    cin >> numDirs;
    work_space = new dir[numDirs];
    char ch;
    for (int i = 0; i < numDirs; i++)
    {
        work_space[i].nameLen = 0;
        getchar(); //new line
        while ((ch = getchar()) != ' ')
            work_space[i].nameLen++;
        cin >> work_space[i].numCont;
        if (work_space[i].numCont != 0)
        {
            work_space[i].contains = new int[work_space[i].numCont];
            for (int j = 0; j < work_space[i].numCont; j++)
            {
                cin >> work_space[i].contains[j];
                work_space[i].contains[j]--;
            }
            work_space[i].is_file = false;
        }
        else
            work_space[i].is_file = true;
    }
    int root = findRoot(numDirs);
    finishDirInfo(root);
    long long ans = work_space[root].charsDown;
    long long curr;
    totalFiles = work_space[root].filesInside;
    for (int i = 0; i < work_space[root].numCont; i++)
    {
        curr = bestLen(work_space[root].contains[i],
                       work_space[root].charsDown);
        ans = min(ans, curr);
    }
    cout << ans;
    return 0;
}