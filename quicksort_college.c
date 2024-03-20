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
// partition for last element as pivot
int partition_1(int array[], int low, int high)
{
    int pivot = array[high];
    int i, j;
    i = low - 1;
    j = low;

    for (j = low; j <= high - 1; j++)
    {
        if (array[j] <= pivot)
        {
            i++;
            swap(&array[i], &array[j]);
            compare++;
        }
    }
    i++;
    swap(&array[i], &array[high]);
    return i;
}
// partition for starting element as pivot
int partition_2(int array[], int low, int high)
{
    int pivot = array[low];
    int i, j;
    i = high + 1;
    j = high;

    for (j = high; j > low; j--)
    {
        if (array[j] >= pivot)
        {
            i--;
            swap(&array[i], &array[j]);
            compare++;
        }
    }
    i--;
    swap(&array[i], &array[low]);
    return i;
}
// partition for mid element as pivot
int partition_3(int array[], int low, int high)
{
    int mid = (low + high) / 2;
    swap(&array[mid], &array[high]);
    int pivot = array[high];
    int i, j;
    i = low - 1;
    j = low;

    for (j = low; j <= high - 1; j++)
    {
        if (array[j] <= pivot)
        {
            i++;
            swap(&array[i], &array[j]);
            compare++;
        }
    }
    i++;
    swap(&array[i], &array[high]);
    return i;
}
void quicksort(int array[], int low, int high, int opt)
{
    if (low < high)
    {
        int pivot;
        if (opt == 1)
        {
            pivot = partition_1(array, low, high);
        }
        if (opt == 2)
        {
            pivot = partition_2(array, low, high);
        }
        if (opt == 3)
        {
            pivot = partition_3(array, low, high);
        }
        quicksort(array, low, pivot - 1, opt);
        quicksort(array, pivot + 1, high, opt);
    }
}
void print(int array[], int start, int end)
{
    int i;
    for (i = start; i <= end; i++)
    {
        printf("%d  ", array[i]);
    }
}
void generatePermutations(int array[], int low, int high, FILE *fp, int opt)
{
    if (low == high)
    {

        for (int i = 0; i <= low; i++)
        {
            fprintf(fp, "%d ", array[i]);
        }
        fprintf(fp, "\n");

        int *temp = (int *)malloc(sizeof(int) * (high - 0 + 1));
        for (int i = 0; i < (high - 0 + 1); i++)
        {
            temp[i] = array[i];
        }
        quicksort(temp, 0, high, opt);
        fprintf(fp, "no of swaps:%d\n", compare);
        compare = 0;
        free(temp);
    }
    else
    {
        for (int i = low; i <= high; i++)
        {
            swap(&array[low], &array[i]);

            generatePermutations(array, low + 1, high, fp, opt);

            swap(&array[low], &array[i]);
        }
    }
}
int main()
{
    srand(time(NULL));
    int size;
    printf("enter size of array\n");
    scanf("%d", &size);

    int *array = (int *)malloc(sizeof(int) * size);
    int i;

    for (i = 0; i < size; i++)
    {
        int num = ((rand() % (100 - 10 + 1)) + 10);
        array[i] = num;
    }

    FILE *fp = fopen("file.txt", "w");
    printf("enter\n1 for pivot at end\n2 for pivot at starting\n3 for pivot at middle\n");
    int opt;
    scanf("%d", &opt);
    generatePermutations(array, 0, size - 1, fp, opt);

    fclose(fp);
    free(array);
    return 0;
}