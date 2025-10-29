#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void swap(int *a, int *b) {
    int t = *a;
    *a = *b;
    *b = t;
}

int partition(int arr[], int low, int high) {
    int pivot = arr[low];
    int i = low;
    int j = high;

    while (i < j) {
        while (i <= high - 1 && arr[i] <= pivot) {
            i++;
        }
        while (j >= low + 1 && arr[j] > pivot) {
            j--;
        }
        if (i < j) {
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[low], &arr[j]);
    return j;
}

void generateRandomArray(int arr[], int n){
    for (int i = 0; i < n; i++){
        arr[i] = rand() % 100000;
    }
}

void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pIndex = partition(arr, low, high);
        quickSort(arr, low, pIndex - 1);
        quickSort(arr, pIndex + 1, high);
    }
}

int main() {
    int n;
    int repetitions;
    printf("Enter the number of repetitions: ");
    scanf("%d", &repetitions);

    for (int i = 0; i < repetitions; i++){
        int n;
        printf("Enter the number of elements: ");
        scanf("%d", &n);

        if (n < 10){
            printf("Please enter a value greater than or equal to 10\n");
            continue;
        }

        int *arr = (int*)malloc(n * sizeof(int));
        if (arr == NULL) {
            printf("Memory allocation failed\n");
            return 1;
        }

        generateRandomArray(arr, n); 
        
        clock_t start = clock();
        for (int j = 0; j < 1000; j++){
            quickSort(arr, 0, n - 1);
        }
        clock_t end = clock();

        double time_taken = (double)(end - start) / CLOCKS_PER_SEC / 1000.0;

        printf("Time taken to sort %d elements: %f seconds\n", n, time_taken);
        free(arr);
    }
    
    return 0;

}
