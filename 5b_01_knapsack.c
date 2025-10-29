#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// Recursive function with memoization
int knapsackRec(int W, int val[], int wt[], int n, int **memo) {

    if (n == 0 || W == 0)
        return 0;

    if (memo[n][W] != -1)
        return memo[n][W];

    int pick = 0;

    if (wt[n - 1] <= W)
        pick = val[n - 1] + knapsackRec(W - wt[n - 1], val, wt, n - 1, memo);

    int notPick = knapsackRec(W, val, wt, n - 1, memo);

    memo[n][W] = (pick > notPick) ? pick : notPick;
    return memo[n][W];
}

int memo_01_knapsack(int W, int val[], int wt[], int n) {
    int **memo = (int **)malloc((n + 1) * sizeof(int *));
    for (int i = 0; i <= n; i++) {
        memo[i] = (int *)malloc((W + 1) * sizeof(int));
        for (int j = 0; j <= W; j++)
            memo[i][j] = -1;
    }

    int result = knapsackRec(W, val, wt, n, memo);

    for (int i = 0; i <= n; i++)
        free(memo[i]);
    free(memo);

    return result;
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
            memo_01_knapsack(W, v, w, n);
        }
        clock_t end = clock();

        double time_taken = ((double)(end-start))/CLOCKS_PER_SEC;
        size_t memo_space = sizeof(int) * (n + 1) * (W + 1);
        size_t total_space = (sizeof(int) * n * 2) + memo_space;

        printf("Time taken to maximise profit with  %d elements: %f seconds\n", n, time_taken);
        printf("Estimated space used: %zu bytes\n", total_space);
        free(v);
        free(w);
    }
    return 0;
}