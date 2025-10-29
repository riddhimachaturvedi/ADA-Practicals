#include <stdio.h>
#include <stdlib.h>
#include <time.h>


int binary_search(int *arr, int low, int high, int key){
    while (low <= high){
        int mid = low + (high - low) / 2; 
        
        if (arr[mid] == key){
            return mid;
        } else if (arr[mid] < key) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return -1; 
}

void generateSortedArray(int arr[], int n){
    for (int i = 0; i < n; i++){
        arr[i] = i; 
    }
}

int main(){
    int index = 0;

    int repetitions;
    printf("Enter the number of repetitions: ");
    scanf("%d", &repetitions);

    for (int i = 0; i < repetitions; i++){
        int n;
        printf("Enter the number of elements: ");
        scanf("%d", &n);

        if (n < 1000){
            printf("Please enter a value greater than or equal to 1000\n");
            continue;
        }

        int *arr = (int*)malloc(n * sizeof(int));
        if (arr == NULL) {
            printf("Memory allocation failed\n");
            return 1;
        }

        int key = arr[n-1] + 1;

        generateSortedArray(arr, n); 
        
        clock_t start = clock();
        for (long long i = 0; i < 1000000; i++){
            binary_search(arr, 0, n - 1, key);
        }
        clock_t end = clock();

        double time_taken = (double)(end - start) / CLOCKS_PER_SEC / 1000.0;

        printf("Time taken to search %d elements: %f seconds\n", n, time_taken);
        free(arr);
    }
    
    return 0;
}