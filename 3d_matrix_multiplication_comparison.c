#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void addMatrix(int n, int A[n][n], int B[n][n], int C[n][n]) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            C[i][j] = A[i][j] + B[i][j];
}

void subMatrix(int n, int A[n][n], int B[n][n], int C[n][n]) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            C[i][j] = A[i][j] - B[i][j];
}

void multiplyStrassen(int n, int A[n][n], int B[n][n], int C[n][n]) {
    if (n == 1) { 
        C[0][0] = A[0][0] * B[0][0];
        return;
    }

    int k = n / 2;

    int A11[k][k], A12[k][k], A21[k][k], A22[k][k];
    int B11[k][k], B12[k][k], B21[k][k], B22[k][k];
    int C11[k][k], C12[k][k], C21[k][k], C22[k][k];
    int M1[k][k], M2[k][k], M3[k][k], M4[k][k], M5[k][k], M6[k][k], M7[k][k];
    int T1[k][k], T2[k][k];

    for (int i = 0; i < k; i++) {
        for (int j = 0; j < k; j++) {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + k];
            A21[i][j] = A[i + k][j];
            A22[i][j] = A[i + k][j + k];

            B11[i][j] = B[i][j];
            B12[i][j] = B[i][j + k];
            B21[i][j] = B[i + k][j];
            B22[i][j] = B[i + k][j + k];
        }
    }

    // M1 = (A11 + A22)(B11 + B22)
    addMatrix(k, A11, A22, T1);
    addMatrix(k, B11, B22, T2);
    multiplyStrassen(k, T1, T2, M1);

    // M2 = (A21 + A22)B11
    addMatrix(k, A21, A22, T1);
    multiplyStrassen(k, T1, B11, M2);

    // M3 = A11(B12 - B22)
    subMatrix(k, B12, B22, T1);
    multiplyStrassen(k, A11, T1, M3);

    // M4 = A22(B21 - B11)
    subMatrix(k, B21, B11, T1);
    multiplyStrassen(k, A22, T1, M4);

    // M5 = (A11 + A12)B22
    addMatrix(k, A11, A12, T1);
    multiplyStrassen(k, T1, B22, M5);

    // M6 = (A21 - A11)(B11 + B12)
    subMatrix(k, A21, A11, T1);
    addMatrix(k, B11, B12, T2);
    multiplyStrassen(k, T1, T2, M6);

    // M7 = (A12 - A22)(B21 + B22)
    subMatrix(k, A12, A22, T1);
    addMatrix(k, B21, B22, T2);
    multiplyStrassen(k, T1, T2, M7);

    // C11 = M1 + M4 - M5 + M7
    for (int i = 0; i < k; i++)
        for (int j = 0; j < k; j++)
            C11[i][j] = M1[i][j] + M4[i][j] - M5[i][j] + M7[i][j];

    // C12 = M3 + M5
    for (int i = 0; i < k; i++)
        for (int j = 0; j < k; j++)
            C12[i][j] = M3[i][j] + M5[i][j];

    // C21 = M2 + M4
    for (int i = 0; i < k; i++)
        for (int j = 0; j < k; j++)
            C21[i][j] = M2[i][j] + M4[i][j];

    // C22 = M1 - M2 + M3 + M6
    for (int i = 0; i < k; i++)
        for (int j = 0; j < k; j++)
            C22[i][j] = M1[i][j] - M2[i][j] + M3[i][j] + M6[i][j];

    // Combine results into C
    for (int i = 0; i < k; i++) {
        for (int j = 0; j < k; j++) {
            C[i][j]         = C11[i][j];
            C[i][j + k]     = C12[i][j];
            C[i + k][j]     = C21[i][j];
            C[i + k][j + k] = C22[i][j];
        }
    }
}

void generateRandomMatrix(int n, int matrix[n][n]) {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            matrix[i][j] = rand() % 10;
}

void multiplyIterative(int n, int matrix1[n][n], int matrix2[n][n], int result[n][n]) {
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
        printf("Enter the size of the matrix (n x n): ");
        scanf("%d", &n);

        int A[n][n], B[n][n], C[n][n];

        generateRandomMatrix(n, A);
        generateRandomMatrix(n, B);

        clock_t start1 =  clock(); 
        for (int i = 0; i < 1000; i++){ 
        multiplyIterative(n, A, B, C);
        }
        clock_t end1 = clock();

        double time_taken1 = ((double)(end1 - start1)) / CLOCKS_PER_SEC / 1000.0;
        printf("Time taken for multiplication of %dx%d matrix (Iterative): %f seconds\n", n, n, time_taken1);

        clock_t start2 = clock();
        for (int i = 0; i < 1000; i++) {
            for (int x = 0; x < n; x++)
                for (int y = 0; y < n; y++)
                    C[x][y] = 0;

            multiplyRecursive(n, A, B, C, 0, 0, 0, 0, 0, 0);
        }
        clock_t end2 = clock();

        double time_taken2 = ((double)(end2 - start2)) / CLOCKS_PER_SEC / 1000.0;
        printf("Time taken for multiplication of %dx%d matrix (Recursive): %f seconds\n", n, n, time_taken2);

        clock_t start3 = clock();
        for (int i = 0; i < 1000; i++) { 
            multiplyStrassen(n, A, B, C);
        }
        clock_t end3 = clock();

        double time_taken3 = ((double)(end3 - start3)) / CLOCKS_PER_SEC / 1000.0;
        printf("Time taken for multiplication of %dx%d matrix (Strassen): %f seconds\n", n, n, time_taken3);

    }

    return 0;
}
