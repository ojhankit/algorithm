#include <stdio.h>
#include <stdlib.h>

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}
void print(int arr[], int size)
{
    for (int i = 0; i < size; i++)
    {
        printf("%d  ", arr[i]);
    }
    printf("\n");
}
void printPermutations(int arr[], int size, int index)
{
    if (index == size - 1)
    {
        print(arr, size);
        return;
    }
    for (int i = index; i < size; i++)
    {
        swap(&arr[index], &arr[i]);
        printPermutations(arr, size, index + 1);
        swap(&arr[index], &arr[i]);
    }
}

int main()
{

    int arr[3] = {1, 2, 3};
    int size = sizeof(arr) / sizeof(int);
    printPermutations(arr, size, 0);

    return 0;
}