#include <stdio.h>
#include <limits.h>

#define MAX 100
#define INF INT_MAX

struct Edge {
    int src, dest, weight;
};

int main() {
    int n, e, src;
    struct Edge edges[MAX];
    int dist[MAX];

    printf("Enter number of vertices: ");
    scanf("%d", &n);

    printf("Enter number of edges: ");
    scanf("%d", &e);

    printf("Enter edges in (u v weight) format:\n");
    for (int i = 0; i < e; i++)
        scanf("%d %d %d", &edges[i].src, &edges[i].dest, &edges[i].weight);

    printf("Enter source vertex (0 to %d): ", n - 1);
    scanf("%d", &src);

    for (int i = 0; i < n; i++)
        dist[i] = INF;
    dist[src] = 0;

    for (int i = 1; i <= n - 1; i++) {
        for (int j = 0; j < e; j++) {
            int u = edges[j].src;
            int v = edges[j].dest;
            int w = edges[j].weight;

            if (dist[u] != INF && dist[u] + w < dist[v])
                dist[v] = dist[u] + w;
        }
    }

    for (int j = 0; j < e; j++) {
        int u = edges[j].src;
        int v = edges[j].dest;
        int w = edges[j].weight;

        if (dist[u] != INF && dist[u] + w < dist[v]) {
            printf("\nGraph contains a NEGATIVE weight cycle!\n");
            return 0;
        }
    }

    printf("\nShortest distance from source %d:\n", src);
    for (int i = 0; i < n; i++)
        if (dist[i] == INT_MAX)
            printf("Node %d -> INF\n", i);
        else
            printf("Node %d -> %d\n", i, dist[i]);
    return 0;
}
