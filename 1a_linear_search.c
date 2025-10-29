#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int linearsearch(int *arr, int size, int key){
    for (int i = 0; i < size; i++) {
        if (arr[i] == key){
            return i;
        }
    }
    return -1;
}

void generateRandomArray(int arr[], int n){
    for (int i = 0; i < n; i++){
        arr[i] = rand() % 100000; //Generate random integers
    }
}


int main(){    
    int index = 0;
    
    int key;
    printf("Enter the element to be searched (key): ");
    scanf("%d", &key);


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

        generateRandomArray(arr, n); 
        
        clock_t start = clock();
        for (int j = 0; j < 1000; j++){
            linearsearch(arr, n, key);
        }
        clock_t end = clock();

        double time_taken = (double)(end - start) / CLOCKS_PER_SEC / 1000.0;

        printf("Time taken to search %d elements: %f seconds\n", n, time_taken);
        free(arr);
    }
    
    return 0;
}
