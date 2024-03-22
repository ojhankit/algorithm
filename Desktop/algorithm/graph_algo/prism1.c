#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct node
{
    int vertex;
    int weight;
    struct node *next;
} node;

typedef struct graph
{
    int V;
    node **adjlist;
} graph;

typedef struct edge
{
    int v1;
    int v2;
    int cost;
} edge;

graph *createGraph(int numV)
{
    graph *newgraph = (graph *)malloc(sizeof(graph));
    newgraph->V = numV;
    newgraph->adjlist = (node **)malloc(sizeof(node *) * newgraph->V);
    int i;
    for (i = 0; i < newgraph->V; i++)
    {
        newgraph->adjlist[i] = NULL;
    }
    return newgraph;
};

void addEdge(graph *Graph, int v1, int v2, int weight)
{
    node *newNode = (node *)malloc(sizeof(node));
    newNode->vertex = v2;
    newNode->weight = weight;
    newNode->next = Graph->adjlist[v1];
    Graph->adjlist[v1] = newNode;

    newNode = (node *)malloc(sizeof(node));
    newNode->vertex = v1;
    newNode->weight = weight;
    newNode->next = Graph->adjlist[v2];
    Graph->adjlist[v2] = newNode;
}

int findMinKey(int *key, int *mstSet, int V)
{
    int min = INT_MAX, min_index;

    for (int v = 0; v < V; v++)
    {
        if (mstSet[v] == 0 && key[v] < min)
        {
            min = key[v];
            min_index = v;
        }
    }

    return min_index;
}

void printMST(int *parent, graph *Graph)
{
    printf("Edge   Weight\n");
    // int sum = 0;
    for (int i = 1; i < Graph->V; i++)
    {
        printf("%d - %d    %d \n", parent[i], i, Graph->adjlist[i]->weight);
        // sum += Graph->adjlist[i]->weight;
    }
    // printf("minimum-cost: %d ", sum);
}

void primMST(graph *Graph)
{
    int V = Graph->V;
    int *parent = (int *)malloc(sizeof(int) * V);
    int *key = (int *)malloc(sizeof(int) * V);
    int *mstSet = (int *)malloc(sizeof(int) * V);

    for (int i = 0; i < V; i++)
    {
        key[i] = INT_MAX;
        mstSet[i] = 0;
    }

    key[0] = 0;
    parent[0] = -1;

    for (int count = 0; count < V - 1; count++)
    {
        int u = findMinKey(key, mstSet, V);
        mstSet[u] = 1;

        node *adjNode = Graph->adjlist[u];
        while (adjNode != NULL)
        {
            int v = adjNode->vertex;
            int weight = adjNode->weight;
            if (mstSet[v] == 0 && weight < key[v])
            {
                parent[v] = u;
                key[v] = weight;
            }
            adjNode = adjNode->next;
        }
    }

    printMST(parent, Graph);
}

int main()
{
    int numV;
    printf("Enter the number of vertices: ");
    scanf("%d", &numV);
    graph *Graph = createGraph(numV);

    FILE *file = fopen("kruskal.txt", "r");
    if (file == NULL)
    {
        printf("Error occur while opening this file\n");
        return -1;
    }

    int v1, v2, cost;
    while (fscanf(file, "%d %d %d", &v1, &v2, &cost) == 3)
    {
        addEdge(Graph, v1 - 1, v2 - 1, cost);
    }

    fclose(file);

    primMST(Graph);

    return 0;
}
