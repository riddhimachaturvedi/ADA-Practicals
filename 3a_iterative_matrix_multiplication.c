#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void generateRandomMatrix(int n, int matrix[n][n]) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            matrix[i][j] = rand() % 10; 
        }
    }
}

void multiplyMatrices(int n, int matrix1[n][n], int matrix2[n][n], int result[n][n]) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            result[i][j] = 0;
        }
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                result[i][j] += matrix1[i][k] * matrix2[k][j];
            }
        }
    }
}

int main() {
    srand(time(NULL));

    for (int t = 1; t <= 5; t++) {
        int n;
        printf("Enter the size of the matrix (n x n): ");
        scanf("%d", &n);

        int matrix1[n][n], matrix2[n][n], result[n][n];

        generateRandomMatrix(n, matrix1);
        generateRandomMatrix(n, matrix2);

        clock_t start =  clock(); 
        for (int i = 0; i < 1000; i++){ 
        multiplyMatrices(n, matrix1, matrix2, result);
        }
        clock_t end = clock();

        double time_taken = ((double)(end-start))/CLOCKS_PER_SEC/1000.0; 
        printf("Time taken to multiply matrix of size %d*%d: %f seconds\n", n, n, time_taken);

    }

    return 0;
}
