#include <stdio.h>
#include <stdlib.h>

void print(int curr[], int currIndex)
{
    for (int i = 0; i < currIndex; i++)
    {
        printf("%d  ", curr[i]);
    }
}
void subsequence(int arr[], int size, int index, int curr[], int currIndex)
{
    if (index == size)
    {
        print(curr, currIndex);
        printf("\n");
        return;
    }
    // take
    curr[currIndex] = arr[index];
    subsequence(arr, size, index + 1, curr, currIndex + 1);

    // not take
    subsequence(arr, size, index + 1, curr, currIndex);
}
int main()
{
    int arr[3] = {3, 1, 2};
    int size, index;
    size = sizeof(arr) / sizeof(int);
    index = 0;
    int *curr = (int *)malloc(sizeof(int) * size);
    int currIndex = 0;
    subsequence(arr, size, index, curr, currIndex);

    free(curr);
    return 0;
}