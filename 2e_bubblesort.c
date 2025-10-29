#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void bubblesort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                int temp = arr[j];
                arr[j] = arr[j + 1];
                arr[j + 1] = temp;
            }
        }
    }
}


void generateRandomArray(int arr[], int n){
    for (int i = 0; i < n; i++){
        arr[i] = rand() % 100000;
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
            bubblesort(arr, n);
        }
        clock_t end = clock();

        double time_taken = (double)(end - start) / CLOCKS_PER_SEC / 1000.0;

        printf("Time taken to sort %d elements: %f seconds\n", n, time_taken);
        free(arr);
    }
    
    return 0;

}