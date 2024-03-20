#include <stdio.h>
#include <stdlib.h>
#define MAX_EDGES 100

typedef struct object
{
    int size;
    struct node *head;
    struct node *tail;
} object;

typedef struct node
{
    int data;
    struct node *next;
    object *prev;
} node;

typedef struct Edge
{
    int vertex1;
    int vertex2;
    int weight;
} Edge;

// Function prototypes
object *make_set(int data);
object *find(object *obj);
void Union(object *obj1, object *obj2);
void merge(Edge arr[], int low, int mid, int high);
void sort(Edge arr[], int low, int high);
void kruskal(Edge edge_array[], int edge_count);

object *make_set(int data)
{
    object *new_obj = (object *)malloc(sizeof(object));
    node *new_node = (node *)malloc(sizeof(node));
    new_obj->head = new_obj->tail = new_node;
    new_obj->size = 1;
    new_node->data = data;
    new_node->next = NULL;
    new_node->prev = new_obj;
    return new_obj;
}

object *find(object *obj)
{
    return obj->head->prev;
}

void Union(object *obj1, object *obj2)
{
    if (find(obj1) != find(obj2))
    {
        object *par1 = obj1->head->prev;
        object *par2 = obj2->head->prev;

        if (par1->size >= par2->size)
        {
            node *temp = par2->head;
            node *prev;
            while (temp != NULL)
            {
                prev = temp;
                temp->prev = par1;
                temp = temp->next;
            }
            par1->tail->next = par2->head;
            par1->tail = prev;
            par1->size += par2->size;
            return;
        }
        else
        {
            node *temp = par1->head;
            node *prev;
            while (temp != NULL)
            {
                prev = temp;
                temp->prev = par2;
                temp = temp->next;
            }
            par2->tail->next = par1->head;
            par2->tail = prev;
            par2->size += par1->size;
            return;
        }
    }
}

void merge(Edge arr[], int low, int mid, int high)
{
    int i = low;
    int j = mid + 1;
    Edge *temp = (Edge *)malloc(sizeof(Edge) * (high - low + 1));
    int k = 0;

    while (i <= mid && j <= high)
    {
        if (arr[i].weight <= arr[j].weight)
        {
            temp[k++] = arr[i++];
        }
        else
        {
            temp[k++] = arr[j++];
        }
    }

    while (i <= mid)
    {
        temp[k++] = arr[i++];
    }
    while (j <= high)
    {
        temp[k++] = arr[j++];
    }
    int x;
    for (x = 0; x < (high - low + 1); x++)
    {
        arr[low + x] = temp[x];
    }
}

void sort(Edge arr[], int low, int high)
{
    if (high - low == 0)
    {
        return;
    }
    int mid = (low + high) / 2;
    sort(arr, low, mid);
    sort(arr, mid + 1, high);
    merge(arr, low, mid, high);
}

void kruskal(Edge edge_array[], int edge_count)
{
    // array for storing MST
    Edge mst[edge_count];
    int mst_size = 0;

    object *parent[MAX_EDGES];

    for (int i = 0; i < edge_count; i++)
    {
        parent[i] = make_set(i);
    }

    for (int i = 0; i < edge_count; i++)
    {
        Edge current_edge = edge_array[i];

        // Find the parent sets of the vertices of the current edge
        object *parent1 = find(parent[current_edge.vertex1]);
        object *parent2 = find(parent[current_edge.vertex2]);

        // check for cycle if not perform UNION
        if (parent1 != parent2)
        {
            mst[mst_size++] = current_edge;
            // Merge the two sets
            Union(parent1, parent2);
        }
    }

    // Print the MST
    printf("Minimum Spanning Tree:\n");
    int cost = 0;
    for (int i = 0; i < mst_size; i++)
    {
        printf("%c-%c=%d\n", mst[i].vertex1 + 64, mst[i].vertex2 + 64, mst[i].weight);
        cost += mst[i].weight;
    }
    printf("Total cost:%d", cost);
}

int main()
{
    FILE *file = fopen("kruskal.txt", "r");
    if (file == NULL)
    {
        perror("Error opening file");
        return 1;
    }

    int source[MAX_EDGES];
    int destination[MAX_EDGES];
    int weight[MAX_EDGES];
    int edge_count = 0;

    // Read each line until the end of the file
    while (fscanf(file, "%d %d %d", &source[edge_count], &destination[edge_count], &weight[edge_count]) == 3)
    {
        edge_count++;
    }

    // Close the file
    fclose(file);

    // sort the edges based on weights
    Edge edge_array[edge_count];
    for (int i = 0; i < edge_count; i++)
    {
        edge_array[i].vertex1 = source[i];
        edge_array[i].vertex2 = destination[i];
        edge_array[i].weight = weight[i];
    }
    sort(edge_array, 0, edge_count - 1);

    printf("Sorted edges\n");
    for (int i = 0; i < edge_count; i++)
    {
        printf("%d\n", edge_array[i].weight);
    }

    for (int i = 0; i < edge_count; i++)
    {
        printf("%c-%c=%d\n", edge_array[i].vertex1 + 64, edge_array[i].vertex2 + 64, edge_array[i].weight);
    }

    kruskal(edge_array, edge_count);
    return 0;
}
