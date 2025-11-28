#include <stdio.h>
#include <stdlib.h>

#define MAX 100

int adjMatrix[MAX][MAX];
int visited[MAX];
int n; 

//ADJACENCY LIST
typedef struct Node {
    int vertex;
    struct Node* next;
} Node;

Node* adjList[MAX];

//FUNCTION TO ADD EDGE
void addEdge(int u, int v) {

    // adjacency list
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->vertex = v;
    newNode->next = adjList[u];
    adjList[u] = newNode;

    // adjacency matrix
    adjMatrix[u][v] = 1;
}

//BFS FUNCTION
void BFS(int start) {
    int queue[MAX], front = 0, rear = 0;
    for (int i = 0; i < n; i++)
        visited[i] = 0;

    visited[start] = 1;
    queue[rear++] = start;

    printf("BFS Traversal: ");
    while (front < rear) {
        int v = queue[front++];
        printf("%d ", v);

        Node* temp = adjList[v];
        while (temp != NULL) {
            int u = temp->vertex;
            if (!visited[u]) {
                visited[u] = 1;
                queue[rear++] = u;
            }
            temp = temp->next;
        }
    }
    printf("\n");
}

//DFS FUNCTION-
void DFSUtil(int v) {
    visited[v] = 1;
    printf("%d ", v);

    Node* temp = adjList[v];
    while (temp != NULL) {
        if (!visited[temp->vertex])
            DFSUtil(temp->vertex);
        temp = temp->next;
    }
}

void DFS(int start) {
    for (int i = 0; i < n; i++)
        visited[i] = 0;

    printf("DFS Traversal: ");
    DFSUtil(start);
    printf("\n");
}

int main() {
    int edges, u, v, start;

    printf("Enter number of vertices: ");
    scanf("%d", &n);

    // initialize adjacency list & matrix
    for (int i = 0; i < n; i++) {
        adjList[i] = NULL;
        for (int j = 0; j < n; j++)
            adjMatrix[i][j] = 0;
    }

    printf("Enter number of edges: ");
    scanf("%d", &edges);

    printf("Enter edges (u v):\n");
    for (int i = 0; i < edges; i++) {
        scanf("%d %d", &u, &v);
        addEdge(u, v);
        addEdge(v, u); // for undirected graph
    }

    printf("\nAdjacency Matrix:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++)
            printf("%d ", adjMatrix[i][j]);
        printf("\n");
    }

    printf("\nAdjacency List:\n");
    for (int i = 0; i < n; i++) {
        printf("%d -> ", i);
        Node* temp = adjList[i];
        while (temp != NULL) {
            printf("%d ", temp->vertex);
            temp = temp->next;
        }
        printf("\n");
    }

    printf("\nEnter starting vertex for BFS and DFS: ");
    scanf("%d", &start);

    BFS(start);
    DFS(start);

    return 0;
}
