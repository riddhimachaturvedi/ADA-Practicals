#include <stdio.h>
#include <limits.h>
#include <time.h>

#define MAX 100
#define INF INT_MAX

void inputGraph(int graph[MAX][MAX], int *n) {
    int i, j;
    printf("Enter number of vertices: ");
    scanf("%d", n);

    printf("Enter adjacency matrix (0 for no edge):\n");
    for (i = 0; i < *n; i++)
        for (j = 0; j < *n; j++)
            scanf("%d", &graph[i][j]);
}

int getMinVertex(int dist[MAX], int visited[MAX], int n) {
    int min = INF, minIndex = -1;
    for (int i = 0; i < n; i++)
        if (!visited[i] && dist[i] < min)
            min = dist[i], minIndex = i;
    return minIndex;
}

void dijkstra(int graph[MAX][MAX], int n, int src, int dist[MAX]) {
    int visited[MAX] = {0};

    for (int i = 0; i < n; i++)
        dist[i] = INF;

    dist[src] = 0;

    for (int count = 0; count < n - 1; count++) {
        int u = getMinVertex(dist, visited, n);
        visited[u] = 1;

        for (int v = 0; v < n; v++)
            if (graph[u][v] && dist[u] != INF &&
                dist[u] + graph[u][v] < dist[v])
                dist[v] = dist[u] + graph[u][v];
    }
}

void printDistances(int dist[MAX], int n, int src) {
    printf("\nShortest distances from source %d:\n", src);
    for (int i = 0; i < n; i++)
        printf("Node %d -> %d\n", i, dist[i]);
}

int main() {
    int n, src;
    int graph[MAX][MAX], dist[MAX];

    inputGraph(graph, &n);

    printf("Enter source vertex (0 to %d): ", n - 1);
    scanf("%d", &src);

    clock_t start = clock();
        for (int j = 0; j < 1000000; j++){
            dijkstra(graph, n, src, dist);

        }
    clock_t end = clock();
    printDistances(dist, n, src);

    double time_taken = (double)(end - start) / CLOCKS_PER_SEC / 1000.0;
    printf("Time taken to implement Dijkstra's Algorithm using Array: %f seconds\n", time_taken);

    return 0;
}
