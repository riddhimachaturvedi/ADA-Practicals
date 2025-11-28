#include <stdio.h>
#include <stdlib.h>

// Comparator function to use in sorting
int comparator(const void *a, const void *b)
{
    const int *p1 = (const int *)a;
    const int *p2 = (const int *)b;
    return p1[2] - p2[2];
}

// Initialization of parent[] and rank[] arrays
void makeSet(int parent[], int rank[], int n)
{
    for (int i = 0; i < n; i++) {
        parent[i] = i;
        rank[i] = 0;
    }
}

int findParent(int parent[], int component)
{
    if (parent[component] == component)
        return component;

    return parent[component]
           = findParent(parent, parent[component]);
}

void unionSet(int u, int v, int parent[], int rank[])
{
    u = findParent(parent, u);
    v = findParent(parent, v);

    if (rank[u] < rank[v]) {
        parent[u] = v;
    }
    else if (rank[u] > rank[v]) {
        parent[v] = u;
    }
    else {
        parent[v] = u;
        rank[u]++;
    }
}

// Function to find the MST
int kruskalAlgo(int V, int E, int edge[E][3])
{
    qsort(edge, E, sizeof(edge[0]), comparator);

    int parent[V];
    int rank[V];
    makeSet(parent, rank, V);

    int minCost = 0;
    int edgesUsed = 0;

    printf("Edge \tWeight\n");

    for (int i = 0; i < E; i++) {

        if (edgesUsed == V - 1)   // STOP here
            break;

        int u = edge[i][0];
        int v = edge[i][1];
        int wt = edge[i][2];

        int setU = findParent(parent, u);
        int setV = findParent(parent, v);

        if (setU != setV) {
            printf("%d - %d \t%d\n", u, v, wt);
            minCost += wt;
            unionSet(setU, setV, parent, rank);

            edgesUsed++;  // one more edge added to MST
        }
    }

    printf("Minimum Cost of MST: %d\n", minCost);
    return minCost;
}


int main()
{
    int V = 4; // number of vertices
    int E = 5; // number of edges
    int edge[5][3] = {
        {0, 1, 10},
        {0, 2, 6},
        {0, 3, 5},
        {1, 3, 15},
        {2, 3, 4}
    };

    kruskalAlgo(V, E, edge);
    return 0;
}