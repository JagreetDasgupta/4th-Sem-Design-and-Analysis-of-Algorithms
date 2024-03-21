#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 1000
#define INF 999999

// Define a structure for a graph
struct Graph {
	int V;
	int** adjMatrix;
};
// Function to create a new graph
struct Graph* createGraph(int V) {
	struct Graph* graph = (struct Graph*)malloc(sizeof(struct Graph));
	graph->V = V;
	// Allocate memory for the adjacency matrix
	graph->adjMatrix = (int**)malloc(V * sizeof(int*));
	for (int i = 0; i < V; i++) {
		graph->adjMatrix[i] = (int*)malloc(V * sizeof(int));
		for (int j = 0; j < V; j++) {
			graph->adjMatrix[i][j] = INF; // Initialize with infinity
		}
	}
	return graph;
}

// Function to add an edge to the graph
void addEdge(struct Graph* graph, int src, int dest, int weight) {
	graph->adjMatrix[src][dest] = weight;
	graph->adjMatrix[dest][src] = weight;
}

// Function to find the minimum key value node
int minKey(int key[], int mstSet[], int V) {
	int min = INF, min_index;
	for (int v = 0; v < V; ++v) {
		if (mstSet[v] == 0 && key[v] < min) { // Changed condition to mstSet[v] == 0
			min = key[v];
			min_index = v;
		}
	}
	return min_index;
}

// Function to print the minimum spanning tree
void printMST(int parent[], struct Graph* graph) {
	printf("Edge \t\tWeight\n");
	int totalWeight = 0;
	for (int i = 1; i < graph->V; ++i) {
		printf("%c -- %c \t\t%d\n",((char)(parent[i] + 1)+'A'),((char)(i + 1)+'A'), graph->adjMatrix[i][parent[i]]);
		totalWeight += graph->adjMatrix[i][parent[i]];
	}
	printf("Total weight of the MST = %d\n", totalWeight);
}

// Function to perform Prim's algorithm
void primMST(struct Graph* graph) {
	int parent[MAX_VERTICES];
	int key[MAX_VERTICES];
	int mstSet[MAX_VERTICES] = {0}; // Initialize mstSet to 0
	for (int i = 0; i < graph->V; ++i) {
		key[i] = INF;
	}
	key[0] = 0;
	parent[0] = -1;
	for (int count = 0; count < graph->V - 1; ++count) {
		int u = minKey(key, mstSet, graph->V);
		mstSet[u] = 1;
		for (int v = 0; v < graph->V; ++v) {
			if (graph->adjMatrix[u][v] && mstSet[v] == 0 && graph->adjMatrix[u][v] < key[v]) {
				parent[v] = u;
				key[v] = graph->adjMatrix[u][v];
			}
		}
	}
	printMST(parent, graph);
}

int main() {
	int vertices = 9;
	FILE* file = fopen("graph.txt", "r");
	if (file == NULL) {
		printf("Error opening file\n");
		exit(1);
	}
	struct Graph* graph = createGraph(vertices);
	int src, dest, weight;
	while (fscanf(file, "%d %d %d", &src, &dest, &weight) != EOF) {
		addEdge(graph, src - 1, dest - 1, weight); // Remove the -1 adjustment here
	}
	fclose(file);
	primMST(graph);
	return 0;
}
