#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int maxDepth = 0;
int currentDepth = 0;

int fib(int n) {
    currentDepth++;
    if (currentDepth > maxDepth) {
        maxDepth = currentDepth;
    }

    int result;
    if (n <= 1) {
        result = n;
    } else {
        result = fib(n - 1) + fib(n - 2);
    }

    currentDepth--;
    return result;
}

int main() {
    srand(time(NULL));

    for (int t = 1; t <= 5; t++) {
        int terms;
        printf("Enter the number of terms: ");
        scanf("%d", &terms);

        maxDepth = 0;
        currentDepth = 0;

        clock_t start = clock();
        for (int i = 0; i < 1000; i++) {
            for (int j = 0; j < terms; j++) {
                fib(j);
            }
        }
        clock_t end = clock();

        double time_taken = ((double)(end - start)) / CLOCKS_PER_SEC / 1000.0;

        printf("Time taken to generate %d terms (recursion): %f seconds\n", terms, time_taken);
        printf("Approximate space used (max recursion depth): %d stack frames\n", maxDepth);
    }

    return 0;
}
