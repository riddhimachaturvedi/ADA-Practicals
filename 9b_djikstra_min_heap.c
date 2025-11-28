#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <time.h>

#define MAX 100
#define INF INT_MAX

struct MinHeapNode {
    int v;
    int dist;
};

struct MinHeap {
    int size;
    int pos[MAX];
    struct MinHeapNode* array[MAX];
};

struct MinHeapNode* newNode(int v, int dist) {
    struct MinHeapNode* node = (struct MinHeapNode*)malloc(sizeof(struct MinHeapNode));
    node->v = v;
    node->dist = dist;
    return node;
}

struct MinHeap* createMinHeap(int n) {
    struct MinHeap* heap = (struct MinHeap*)malloc(sizeof(struct MinHeap));
    heap->size = 0;
    for (int i = 0; i < n; i++) {
        heap->pos[i] = i;
        heap->array[i] = NULL;
    }
    return heap;
}

void swapNodes(struct MinHeapNode** a, struct MinHeapNode** b) {
    struct MinHeapNode* temp = *a;
    *a = *b;
    *b = temp;
}

void heapify(struct MinHeap* heap, int idx) {
    int smallest = idx;
    int l = 2 * idx + 1;
    int r = 2 * idx + 2;

    if (l < heap->size && heap->array[l]->dist < heap->array[smallest]->dist)
        smallest = l;
    if (r < heap->size && heap->array[r]->dist < heap->array[smallest]->dist)
        smallest = r;

    if (smallest != idx) {
        struct MinHeapNode* smallNode = heap->array[smallest];
        struct MinHeapNode* idxNode = heap->array[idx];

        heap->pos[smallNode->v] = idx;
        heap->pos[idxNode->v] = smallest;

        swapNodes(&heap->array[smallest], &heap->array[idx]);
        heapify(heap, smallest);
    }
}

int isHeapEmpty(struct MinHeap* heap) {
    return heap->size == 0;
}

struct MinHeapNode* extractMin(struct MinHeap* heap) {
    struct MinHeapNode* root = heap->array[0];
    heap->array[0] = heap->array[heap->size - 1];

    heap->pos[root->v] = heap->size - 1;
    heap->pos[heap->array[0]->v] = 0;

    heap->size--;
    heapify(heap, 0);

    return root;
}

void decreaseKey(struct MinHeap* heap, int v, int dist) {
    int i = heap->pos[v];
    heap->array[i]->dist = dist;

    while (i && heap->array[i]->dist < heap->array[(i - 1) / 2]->dist) {
        heap->pos[heap->array[i]->v] = (i - 1) / 2;
        heap->pos[heap->array[(i - 1) / 2]->v] = i;
        swapNodes(&heap->array[i], &heap->array[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

void inputGraph(int graph[MAX][MAX], int* n) {
    printf("Enter number of vertices: ");
    scanf("%d", n);
    printf("Enter adjacency matrix (0 means no edge):\n");
    for (int i = 0; i < *n; i++)
        for (int j = 0; j < *n; j++)
            scanf("%d", &graph[i][j]);
}

void dijkstraHeap(int graph[MAX][MAX], int n, int src, int dist[MAX]) {
    for (int i = 0; i < n; i++)
        dist[i] = INF;
    dist[src] = 0;

    struct MinHeap* heap = createMinHeap(n);
    for (int v = 0; v < n; v++)
        heap->array[v] = newNode(v, dist[v]);

    heap->size = n;

    while (!isHeapEmpty(heap)) {
        struct MinHeapNode* root = extractMin(heap);
        int u = root->v;

        for (int v = 0; v < n; v++)
            if (graph[u][v] && dist[u] != INF &&
                dist[u] + graph[u][v] < dist[v]) {
                dist[v] = dist[u] + graph[u][v];
                decreaseKey(heap, v, dist[v]);
            }
    }
}

void printResults(int dist[MAX], int n, int src) {
    printf("\nShortest distances from source %d:\n", src);
    for (int i = 0; i < n; i++)
        printf("Node %d -> %d\n", i, dist[i]);
}

int main() {
    int graph[MAX][MAX], dist[MAX], n, src;
    inputGraph(graph, &n);
    printf("Enter source vertex (0 to %d): ", n - 1);
    scanf("%d", &src);

    clock_t start = clock();
        for (int j = 0; j < 1000000; j++){
            dijkstraHeap(graph, n, src, dist);

        }
    clock_t end = clock();
    printResults(dist, n, src);

    double time_taken = (double)(end - start) / CLOCKS_PER_SEC / 1000.0;
    printf("Time taken to implement Dijkstra's Algorithm using Min-Heap: %f seconds\n", time_taken);
    return 0;
}
