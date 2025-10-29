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

void multiplyRecursive(int n, int A[n][n], int B[n][n], int C[n][n],
                       int rowA, int colA, int rowB, int colB, int rowC, int colC) {
    if (n == 1) {
        C[rowC][colC] += A[rowA][colA] * B[rowB][colB];
        return;
    }

    int k = n / 2;

    // C11 = A11*B11 + A12*B21
    multiplyRecursive(k, A, B, C, rowA, colA, rowB, colB, rowC, colC);
    multiplyRecursive(k, A, B, C, rowA, colA + k, rowB + k, colB, rowC, colC);

    // C12 = A11*B12 + A12*B22
    multiplyRecursive(k, A, B, C, rowA, colA, rowB, colB + k, rowC, colC + k);
    multiplyRecursive(k, A, B, C, rowA, colA + k, rowB + k, colB + k, rowC, colC + k);

    // C21 = A21*B11 + A22*B21
    multiplyRecursive(k, A, B, C, rowA + k, colA, rowB, colB, rowC + k, colC);
    multiplyRecursive(k, A, B, C, rowA + k, colA + k, rowB + k, colB, rowC + k, colC);

    // C22 = A21*B12 + A22*B22
    multiplyRecursive(k, A, B, C, rowA + k, colA, rowB, colB + k, rowC + k, colC + k);
    multiplyRecursive(k, A, B, C, rowA + k, colA + k, rowB + k, colB + k, rowC + k, colC + k);
}

int main() {
    srand(time(NULL));

    for (int t = 1; t <= 5; t++) {
        int n;
        printf("Enter the size of the matrix (n x n): ", t);
        scanf("%d", &n);

        int A[n][n], B[n][n], C[n][n];

        generateRandomMatrix(n, A);
        generateRandomMatrix(n, B);

        clock_t start = clock();
        for (int i = 0; i < 1000; i++) {
            for (int x = 0; x < n; x++)
                for (int y = 0; y < n; y++)
                    C[x][y] = 0;

            multiplyRecursive(n, A, B, C, 0, 0, 0, 0, 0, 0);
        }
        clock_t end = clock();

        double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC / 1000.0;
        printf("Time taken to multiply matrix of size %d*%d (recursive): %f seconds\n", n, n, time_taken);
    }

    return 0;
}
