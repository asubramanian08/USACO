#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MIN(X, Y) (((X) < (Y)) ? (X) : (Y))
#define MAX(X, Y) (((X) > (Y)) ? (X) : (Y))
unsigned long long getNum()
{
    unsigned long long total = 0;
    char ch = getchar();
    while ((ch != ' ') && (ch != '\n'))
    {
        total = (total * 10) + (ch - '0');
        ch = getchar();
    }
    return total;
}
unsigned int *id, *sz;
void init(unsigned int N)
{
    id = (unsigned int *)malloc(sizeof(unsigned int) * N);
    sz = (unsigned int *)malloc(sizeof(unsigned int) * N);
    for (unsigned int i = 0; i < N; i++)
    {
        id[i] = i;
        sz[i] = 1;
    }
}
//find its first parent
unsigned int root(unsigned int i)
{
    while (i != id[i])
    {
        id[i] = id[id[i]];
        i = id[i];
    }
    return i;
}
bool is_connected(unsigned int p, unsigned int q) { return root(p) == root(q); }
void connect(unsigned int p, unsigned int q)
{
    unsigned int i = root(p), j = root(q);
    if (i == j)
        return;
    if (sz[i] < sz[j])
    {
        id[i] = j;
        sz[j] += sz[i];
    }
    else
    {
        id[j] = i;
        sz[i] += sz[j];
    }
}

struct conn
{
    unsigned int nd1;
    unsigned int nd2;
    unsigned int rel;
};
struct quest
{
    unsigned int rel;
    unsigned int fromNode;
    unsigned orgOrder;
};
int compareConn(const void *p1, const void *p2)
{
    return ((conn *)p2)->rel - ((conn *)p1)->rel;
}
int compareQuest(const void *p1, const void *p2)
{
    return ((quest *)p2)->rel - ((quest *)p1)->rel;
}
int main(void)
{
    unsigned int vids = getNum(), querys = getNum();
    init(vids);
    conn *conns = (conn *)malloc(sizeof(conn) * (vids - 1));
    for (unsigned int i = 1; i < vids; i++)
    {
        conns[i - 1].nd1 = getNum() - 1;
        conns[i - 1].nd2 = getNum() - 1;
        conns[i - 1].rel = getNum();
    }
    quest *quests = (quest *)malloc(sizeof(quest) * querys);
    for (unsigned int i = 0; i < querys; i++)
    {
        quests[i].rel = getNum();
        quests[i].fromNode = getNum() - 1;
        quests[i].orgOrder = i;
    }
    qsort(conns, vids - 1, sizeof(conn), compareConn);
    qsort(quests, querys, sizeof(quest), compareQuest);

    unsigned int *ans = (unsigned int *)malloc(sizeof(unsigned int) * querys);
    unsigned int currConn = 0;
    for (unsigned int currQuest = 0; currQuest < querys; currQuest++)
    {
        while ((currConn < vids - 1) && (conns[currConn].rel >= quests[currQuest].rel))
        {
            connect(conns[currConn].nd1, conns[currConn].nd2);
            currConn++;
        }
        ans[quests[currQuest].orgOrder] = sz[root(quests[currQuest].fromNode)];
    }
    for (unsigned int i = 0; i < querys; i++)
        printf("%d\n", ans[i] - 1);
    return 0;
}