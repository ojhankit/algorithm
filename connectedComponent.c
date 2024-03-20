#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int vertex1;
    int vertex2;
} Edge;

int find(int parent[], int i)
{
    if (parent[i] == i)
        return i;
    return find(parent, parent[i]);
}

void Union(int parent[], int rank[], int a, int b)
{
    int parA = find(parent, a);
    int parB = find(parent, b);

    if (parA != parB)
    {
        if (rank[parA] < rank[parB])
            parent[parA] = parB;
        else if (rank[parA] > rank[parB])
            parent[parB] = parA;
        else
        {
            parent[parA] = parB;
            rank[parB]++;
        }
    }
}

void printTree(int parent[], int size, int root)
{
    printf("%d ", root);
    for (int i = 0; i < size; i++)
    {
        if (parent[i] == root && i != root)
        {
            printf("-> ");
            printTree(parent, size, i);
        }
    }
}

void printSets(int parent[], int size)
{
    printf("Disjoint Sets as Trees:\n");
    for (int i = 0; i < size; i++)
    {
        if (parent[i] == i)
        {
            printf("Set %d: ", i);
            printTree(parent, size, i);
            printf("\n");
        }
    }
}

// void print(int parent[], int V)
// {
//     for (int i = 0; i < V; i++)
//     {
//         printf("%d  ", parent[i]);
//     }
//     printf("\n");
// }
int main()
{
    int V, i;
    printf("enter number of vertices\n");
    scanf("%d", &V);
    int parent[V], rank[V];

    // fill the parent array
    for (i = 0; i < V; i++)
    {
        parent[i] = i;
    }

    // fill the rank array
    for (i = 0; i < V; i++)
    {
        rank[i] = 0;
    }

    FILE *file = fopen("graph.txt", "r");

    if (file == NULL)
    {
        printf("Error opening file.\n");
        return 1;
    }

    int vertex1, vertex2;

    // Define an array to store edges
    Edge edges[V];
    int Count = 0;

    while (fscanf(file, "%d %d", &vertex1, &vertex2) == 2)
    {
        printf("Edge: (%d, %d)\n", vertex1, vertex2);
        edges[Count].vertex1 = vertex1 - 1;
        edges[Count].vertex2 = vertex2 - 1;
        Count++;
    }
    printf("edge array display\n");
    for (int i = 0; i < Count; i++)
    {
        printf("%d %d\n", edges[i].vertex1, edges[i].vertex2);
    }
    for (int j = 0; j < Count; j++)
    {
        Union(parent, rank, edges[j].vertex1, edges[j].vertex2);
    }

    // Print the disjoint sets after all unions
    printf("Disjoint Sets after unions:\n");
    printSets(parent, V);

    return 0;
}
