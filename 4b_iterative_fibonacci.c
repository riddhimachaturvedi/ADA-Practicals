#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int fibonacci(int n) {
    if (n == 0) return 0;
    if (n == 1) return 1;

    int t1 = 0, t2 = 1, nextTerm;

    for (int i = 2; i <= n; ++i) {
        nextTerm = t1 + t2;
        t1 = t2;
        t2 = nextTerm;
    }

    return t2;
}

int main() {
    srand(time(NULL));

    for (int t = 1; t <= 5; t++) {
        int terms;
        printf("Enter the number of terms: ");
        scanf("%d", &terms);

        clock_t start = clock();
        for (int i = 0; i < 1000000; i++) {
            for (int j = 0; j < terms; j++) {
                fibonacci(j);
            }
        }
        clock_t end = clock();

        double time_taken = (double)(end - start) / CLOCKS_PER_SEC/1000.0;

    // Memory = sum of sizes of variables used
    size_t memory_used = 4 * sizeof(int); 

    printf("Time taken to generate %d terms (iteration): %f seconds\n", terms, time_taken);
    printf("Approximate space used: %zu bytes\n", memory_used);
    }

    return 0;
}
