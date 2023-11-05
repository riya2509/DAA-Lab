#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define MAX_NODES 1000  // Adjust this based on the maximum number of nodes in the graph

// Structure to represent a node in the adjacency list
typedef struct Node {
    int data;
    struct Node* next;
} Node;

// Structure to represent the adjacency list
typedef struct Graph {
    Node* adjacencyList[MAX_NODES];
} Graph;

// Function to add an edge to the adjacency list
void addEdge(Graph* graph, int u, int v) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->data = v;
    newNode->next = graph->adjacencyList[u];
    graph->adjacencyList[u] = newNode;

    newNode = (Node*)malloc(sizeof(Node));
    newNode->data = u;
    newNode->next = graph->adjacencyList[v];
    graph->adjacencyList[v] = newNode;
}

// Function to perform BFS and calculate distances
void bfs_shortest_distances(Graph* graph, int n, int start, int distances[]) {
    bool visited[MAX_NODES] = {false};
    int queue[MAX_NODES];
    int front = 0, rear = 0;

    queue[rear++] = start;
    visited[start] = true;
    distances[start] = 0;

    while (front < rear) {
        int node = queue[front++];
        Node* current = graph->adjacencyList[node];
        while (current != NULL) {
            int neighbor = current->data;
            if (!visited[neighbor]) {
                distances[neighbor] = distances[node] + 2;
                queue[rear++] = neighbor;
                visited[neighbor] = true;
            }
            current = current->next;
        }
    }
}

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    Graph graph;
    memset(graph.adjacencyList, 0, sizeof(graph.adjacencyList));

    for (int i = 0; i < m; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        addEdge(&graph, u, v);
    }

    int start;
    scanf("%d", &start);

    int distances[MAX_NODES];
    memset(distances, -1, sizeof(distances));

    bfs_shortest_distances(&graph, n, start, distances);

    printf("BFS Traversal Order: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", i);
    }
    printf("\n");

    printf("Shortest Distances from Node %d: ", start);
    for (int i = 1; i <= n; i++) {
        printf("%d ", distances[i]);
    }
    printf("\n");

    return 0;
}