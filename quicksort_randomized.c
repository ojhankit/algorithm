#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int compare = 0;
void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}
void print(int array[], int start, int end)
{
    for (int i = start; i <= end; i++)
    {
        printf("%d\t", array[i]);
    }
}

int partition(int array[], int start, int end)
{
    int randomPivotIndex = (rand() % (end - start + 1)) + start;
    swap(&array[randomPivotIndex], &array[end]);
    int i, j;
    i = start - 1;
    for (j = start; j <= end - 1; j++)
    {
        if (array[j] <= array[end])
        {
            i++;
            swap(&array[i], &array[j]);
            compare++;
        }
    }
    i++;
    swap(&array[i], &array[end]);
    return i;
}

void quicksort(int array[], int start, int end)
{
    if (start < end)
    {
        int pivot = partition(array, start, end);
        quicksort(array, start, pivot - 1);
        quicksort(array, pivot + 1, end);
    }
}
void generatePermutations(int array[], int start, int end, FILE *file)
{
    if (start == end)
    {

        for (int i = 0; i <= end; i++)
        {
            fprintf(file, "%d ", array[i]);
        }
        fprintf(file, "\n");
        int *temp = (int *)malloc(sizeof(int) * (end - 0 + 1));
        int i;
        for (i = 0; i <= end; i++)
        {
            temp[i] = array[i];
        }
        quicksort(temp, 0, end);
        fprintf(file, "no of comparison:%d", compare);
        fprintf(file, "\n");
        free(temp);
        compare = 0;
    }
    else
    {
        for (int i = start; i <= end; i++)
        {
            swap(&array[start], &array[i]);

            generatePermutations(array, start + 1, end, file);

            swap(&array[start], &array[i]);
        }
    }
}
int main()
{
    srand(time(NULL));
    int size;
    printf("enter the size of array\n");
    scanf("%d", &size);
    int *array = (int *)malloc(sizeof(int) * size);
    int i;
    for (i = 0; i < size; i++)
    {
        int num = (rand() % (10 - 1 + 1) + 1);
        array[i] = num;
    }

    FILE *file = fopen("file.txt", "w");

    generatePermutations(array, 0, size - 1, file);

    fclose(file);
    free(array);
}
