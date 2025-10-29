#include <stdio.h>
#include <stdlib.h>
#include <time.h>

float fractional_knapsack(int value[], int weight[], int n, int capacity) {
    float total_value = 0.0f; 
    int used[100] = {0};      

    while (capacity > 0) {
        int max_index = -1;
       
        for (int i = 0; i < n; ++i) {
            if (!used[i] && 
                (max_index == -1 || 
                 (float)value[i] / weight[i] > (float)value[max_index] / weight[max_index])) {
                max_index = i;
            }
        }

        if (max_index == -1)
            break; 

        used[max_index] = 1;

        if (weight[max_index] <= capacity) {
            total_value += value[max_index];
            capacity -= weight[max_index];
        } 

        else {
            total_value += ((float)capacity / weight[max_index]) * value[max_index];
            capacity = 0; 
        }
    }

    return total_value;
}

void generateProfitArray(int arr[], int n){
    for (int i = 0; i < n; i++){
        arr[i] = (rand() % 6) + 1; // Generates numbers from 1 to 6
    }
}


void generateWeightArray(int arr[], int n){
    for (int i = 0; i < n; i++){
        arr[i] = (rand() % 25) + 1; // Generates numbers from 1 to 25
    }
}


int main(){
    srand(time(NULL));

    int sizes[] = {10, 100, 500, 750, 1000};
    for (int i = 0; i < 5; i++){

        int n = sizes[i];
        int W = 10;

        int *v = (int*)malloc(n * sizeof(int));
        if (v == NULL) {
            printf("Memory allocation failed\n");
            return 1; 
        }

        int *w = (int*)malloc(n * sizeof(int)); 
        if (w == NULL) {
            printf("Memory allocation failed\n");
            return 1; 
        }
        generateProfitArray(v, n);
        generateWeightArray(w, n);

        clock_t start =  clock();
        for (int j = 0; j < 1000; j++) {
            fractional_knapsack(v, w, n, W);
        }
        clock_t end = clock();

        double time_taken = ((double)(end-start))/CLOCKS_PER_SEC;
        size_t space_used = (sizeof(int) * n * 2) + (sizeof(int) * 100); 

        printf("Time taken to maximise profit with  %d elements: %f seconds\n", n, time_taken);
        printf("Estimated space used: %zu bytes\n", space_used);
        free(v);
        free(w);
    }
    return 0;
}