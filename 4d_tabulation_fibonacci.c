#include <stdio.h>
#include <stdlib.h>
#include <time.h>

long long nthFibonacci(int n, size_t *mem_used) {
    if (n <= 1) return n;

    long long dp[n + 1];  // array on stack
    *mem_used = sizeof(dp);

    dp[0] = 0;
    dp[1] = 1;

    for (int i = 2; i <= n; ++i) {
        dp[i] = dp[i - 1] + dp[i - 2];
    }

    return dp[n];
}

int main() {
    srand(time(NULL));

    for (int t = 1; t <= 5; t++) {
        int terms;
        printf("Enter the number of terms: ");
        scanf("%d", &terms);
        

        clock_t start = clock();
        size_t memory_used = 0;
        for (int i = 0; i < 1000000; i++) {
            for (int j = 0; j < terms; j++) {
                nthFibonacci(terms, &memory_used);
            }
        }
        clock_t end = clock();

        double time_taken = (double)(end - start) / CLOCKS_PER_SEC/1000.0;

    printf("\nTime taken: %f seconds\n", time_taken);
    printf("Approximate space used: %zu bytes\n", memory_used);
    }
    return 0;

}
