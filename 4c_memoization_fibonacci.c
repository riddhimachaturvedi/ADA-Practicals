#include <stdio.h>
#include <stdlib.h>
#include <time.h>

long long fib_array[100]; 
int maxDepth = 0, currentDepth = 0;

long long fib(int n) {
    currentDepth++;
    if (currentDepth > maxDepth) {
        maxDepth = currentDepth;
    }

    if (n <= 1) {
        currentDepth--;
        return n;
    }

    if (fib_array[n] != 0) {
        currentDepth--;
        return fib_array[n];
    }

    fib_array[n] = fib(n - 1) + fib(n - 2);
    currentDepth--;
    return fib_array[n];
}

int main() {
    srand(time(NULL));

    for (int t = 1; t <= 5; t++) {
        int terms;
        printf("Enter the number of terms: ");
        scanf("%d", &terms);
        
        for (int i = 0; i < 100; i++) {
            fib_array[i] = 0;
        }

        clock_t start = clock();
        for (int i = 0; i < 1000000; i++) {
            for (int j = 0; j < terms; j++) {
                fib(j);
            }
        }
        clock_t end = clock();

        double time_taken = (double)(end - start) / CLOCKS_PER_SEC/1000.0;

    printf("Time taken to generate %d terms: %f seconds\n", terms, time_taken);
    printf("Approximate space used (max recursion depth): %d stack frames\n", maxDepth);
    }

    return 0;
}
