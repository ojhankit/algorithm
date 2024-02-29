#include <stdio.h>

int flag = 1;
int Find(int parent[], int i)
{
    if (parent[i] == i)
    {
        return i;
    }
    return Find(parent, parent[i]);
}
void Union(int parent[], int i, int j)
{
    if (Find(parent, i) == Find(parent, j))
    {
        printf("cycle Detected\n");
        flag = 0;
        return; // i and j are present in same set
    }
    parent[j] = i;
    return;
}
void print(int arr[], int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("%d  ", arr[i]);
    }
}
int main()
{

    int n, e, i, j;
    printf("enter the number of vertices\n");
    scanf("%d", &n);
    printf("enter the number of edges\n");
    scanf("%d", &e);

    int parent[n];
    for (int k = 0; k < n; k++)
    {
        parent[k] = k;
    }

    for (int k = 0; k < e; k++)
    {
        printf("enter the vertex between edge is present\n");
        scanf("%d %d", &i, &j);
        Union(parent, i, j);
        if (flag == 0)
        {
            break;
        }
    }
    if (flag == 1)
    {
        printf("cycle not detected\n");
    }
    return 0;
}