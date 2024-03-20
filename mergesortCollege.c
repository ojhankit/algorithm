#include<stdio.h>
#include<stdlib.h>

void swap(int *a, int *b) {
    int temp = *a;
    *a = *b;
    *b = temp;
}
int compare=0;
void merge(int arr[],int low,int mid,int high){
    int i = low;
    int j = mid + 1;
    int *temp = (int *)malloc((high - low + 1) * sizeof(int));
    int k = 0;

    while (i <= mid && j <= high) {
        if (arr[i] <= arr[j]) {
            temp[k++] = arr[i++];
            compare++;
        } else {
            temp[k++] = arr[j++];
            compare++;
        }
    }

    while (i <= mid) {
        temp[k++] = arr[i++];
    }

    while (j <= high) {
        temp[k++] = arr[j++];
    }

    for (int i = 0; i < (high - low + 1); i++) {
        arr[low + i] = temp[i];
    }

    free(temp);
}

void print(int arr[],int size){
    for(int i=0;i<size;i++){
        printf("%d  ",arr[i]);
    }
}

void mergesort(int arr[],int low,int high){
    if(high-low==0){
        return;
    }
    int mid=(low+high)/2;
    mergesort(arr,low,mid);
    mergesort(arr,mid+1,high);
    merge(arr,low,mid,high);
}

void generatePermutations(int array[], int start, int end, FILE *file) {
    if (start == end) {
        
        for (int i = 0; i <= end; i++) {
            fprintf(file, "%d ", array[i]); // add element of array to the file
        }
        fprintf(file, "\n"); // add newline character to the file
        //  printf("permuted array\n");
        //  print(array,end-0+1);
        //  printf("\n");
         mergesort(array,0,end);
        //  printf("sorted array\n");
         fprintf(file,"no of comparison:%d",compare);
         fprintf(file,"\n");
        //  print(array,end-0+1);
        //  printf("\n");
         compare=0;
    } else {
        for (int i = start; i <= end; i++) {
            swap(&array[start], &array[i]);
            
            generatePermutations(array, start + 1, end, file);
            
            swap(&array[start], &array[i]);
        }
    }
}
int main() {
    int size;
    printf("Enter the size of the array: ");
    scanf("%d", &size);

    int *array = (int *)malloc(size * sizeof(int));
    
    for (int i = 0; i < size; i++) {
        int num=(rand()%(10-1+1))+1; // generating random number between 1 and 10 ((high-low+1))
        array[i]=num;
    }

    FILE *file = fopen("permutations.txt", "w");
    if (file == NULL) {
        printf("Error opening file.\n");
        return 1;
    }
    generatePermutations(array, 0, size - 1, file);
    
    fclose(file);
    free(array);
    
    return 0;
}