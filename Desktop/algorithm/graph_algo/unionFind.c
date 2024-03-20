// connected component using union find algorithm

#include <stdio.h>
#include <stdlib.h>

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
    printf("Hello\n");
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

void printSet(object *obj_array[], int size)
{
    int i;
    int set_no = 0;
    for (i = 0; i < size; i++)
    {
        if (obj_array[i]->head->prev == obj_array[i])
        {
            node *temp = obj_array[i]->head;
            printf("root is %d\n", temp->data);
            if (temp != NULL)
            {
                printf("Set %d: ", ++set_no);
                while (temp != NULL)
                {
                    printf("%d ", temp->data);
                    temp = temp->next;
                }
                printf("\n");
            }
        }
    }
}
int main()
{
    int num;
    printf("enter the number\n");
    scanf("%d", &num);

    object *obj_array[num];

    int i;
    for (i = 0; i < num; i++)
    {
        obj_array[i] = make_set(i + 1);
    }
    FILE *file = fopen("graph.txt", "r");

    int v1, v2;

    while (fscanf(file, "%d %d", &v1, &v2) == 2)
    {
        Union(obj_array[v1 - 1], obj_array[v2 - 1]);
    }

    fclose(file);
    printf("Connected components are:\n");
    printSet(obj_array, num);
    return 0;
}