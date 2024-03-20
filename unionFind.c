#include <stdio.h>
#include <stdlib.h>

struct set;

struct node
{
    int data;
    struct node *next;
    struct set *prev;
};
struct set
{
    struct node *head;
    struct node *tail;
};

struct node *getnode()
{
    struct node *temp = (struct node *)malloc(sizeof(struct node));
    temp->next = NULL;
    temp->prev = NULL;

    return temp;
}
void MakeSet(struct set *element)
{
    struct node *newnode = getnode();
    newnode->prev = element;
    element->head = newnode;
    element->tail = newnode;
}

struct node *find(struct node *element)
{

    return element->prev->head; // Returns the representative element of the set
}
void Union(struct set *set1, struct set *set2)
{
    // Find representatives of both sets
    struct node *rep1 = find(set1->head);
    struct node *rep2 = find(set2->head);

    rep2->prev = set1;
    set1->tail->next = rep2;
    set1->tail = set2->tail;
}
void display(struct set *element)
{
    struct node *temp = (struct node *)element->head;
    while (temp != NULL)
    {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}
int main()
{
    int n;
    printf("enter the number of elements\n");
    scanf("%d", &n);

    struct set array[n];
    // three function i have to implement
    /*
        make set
        union
        find
    */
    for (int i = 0; i < n; i++)
    {
        MakeSet(&array[i]);
        array[i].head->data = i;
    }

    for (int i = 0; i < n; i++)
    {
        printf("%d ", array[i].head->data);
    }
    printf("\n");
    // test cases for union operation
    /*
        here i can put a loop and take input of whatever element i want to make union
    */
    Union(&array[0], &array[1]);
    Union(&array[2], &array[3]);

    // display set after union

    for (int i = 0; i < n; i++)
    {
        display(&array[i]);
    }
    return 0;
}
