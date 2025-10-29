#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void insertionsort(int array[], int size)
{

    for (int i = 0; i < size; i++)
    {
        for (int j = i; j > 0; j--)
        {
            if (array[j] < array[j - 1])
            {
                int temp = array[j];
                array[j] = array[j - 1];
                array[j - 1] = temp;
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
            insertionsort(arr, n);
        }
        clock_t end = clock();

        double time_taken = (double)(end - start) / CLOCKS_PER_SEC / 1000.0;

        printf("Time taken to sort %d elements: %f seconds\n", n, time_taken);
        free(arr);
    }
    
    return 0;

}