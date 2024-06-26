#include <stdio.h>
#include <stdlib.h>
#define V 13
int p[V + 1];
int rank[V + 1];
void makeSet(int x)
{
    p[x] = x;
    rank[x] = 0;
}
int findSet(int x)
{
    if (x != p[x])
    {
        p[x] = findSet(p[x]);
    }
    return p[x];
}
void link(int x, int y)
{
    if (rank[x] > rank[y])
    {
        p[y] = x;
    }
    else
    {
        p[x] = y;
        if (rank[x] == rank[y])
        {
            rank[y]++;
        }
    }
}
void unionSets(int x, int y)
{
    link(findSet(x), findSet(y));
}
int main()
{
    int i, j;
    FILE *file = fopen("rootedtreegraph.txt", "r");
    if (file == NULL)
    {
        perror("Error opening file");
        return 1;
    }
    for (i = 1; i <= V; i++)
    {
        makeSet(i);
    }
    int u, v;
    while (fscanf(file, "%d %d", &u, &v) == 2)
    {
        unionSets(u, v);
    }
    fclose(file);
    int components[V + 1] = {0};
    for (i = 1; i <= V; i++)
    {
        components[findSet(i)]++;
    }
    printf("Connected Components:\n");
    int k = 1;
    for (i = 1; i <= V; i++)
    {
        if (components[i] > 0)
        {
            printf("Component %d: ", k++);
            for (j = 1; j <= V; j++)
            {
                if (findSet(j) == i)
                {
                    printf("%d ", j);
                }
            }
            printf("root: %d", i);
            printf("\n");
        }
    }
    return 0;
}
