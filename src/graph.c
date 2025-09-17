#include "../include/graph.h"

Graph* create_graph(int num_vertices) {
    if (num_vertices <= 0 || num_vertices > MAX_VERTICES) {
        printf("Error: Invalid number of vertices\n");
        return NULL;
    }

    Graph* graph = malloc(sizeof(Graph));
    if (!graph) {
        printf("Error: Memory allocation failed for graph\n");
        return NULL;
    }

    graph->num_vertices = num_vertices;

    graph->adjacency_list = malloc(num_vertices * sizeof(Edge*));
    if (!graph->adjacency_list) {
        printf("Error: Memory allocation failed for adjacency list\n");
        free(graph);
        return NULL;
    }

    graph->vertex_degrees = malloc(num_vertices * sizeof(int));
    if (!graph->vertex_degrees) {
        printf("Error: Memory allocation failed for vertex degrees\n");
        free(graph->adjacency_list);
        free(graph);
        return NULL;
    }

    for (int i = 0; i < num_vertices; i++) {
        graph->adjacency_list[i] = NULL;
        graph->vertex_degrees[i] = 0;
    }

    return graph;
}

void destroy_graph(Graph* graph) {
    if (!graph) return;

    for (int i = 0; i < graph->num_vertices; i++) {
        Edge* current = graph->adjacency_list[i];
        while (current) {
            Edge* temp = current;
            current = current->next;
            free(temp);
        }
    }

    free(graph->adjacency_list);
    free(graph->vertex_degrees);
    free(graph);
}

void add_edge(Graph* graph, int source, int destination, int weight) {
    if (!graph) {
        printf("Error: Graph is NULL\n");
        return;
    }

    if (!is_valid_vertex(graph, source) || !is_valid_vertex(graph, destination)) {
        printf("Error: Invalid vertex indices\n");
        return;
    }

    if (weight < 0) {
        printf("Error: Negative weight not allowed\n");
        return;
    }

    Edge* new_edge = malloc(sizeof(Edge));
    if (!new_edge) {
        printf("Error: Memory allocation failed for edge\n");
        return;
    }

    new_edge->destination = destination;
    new_edge->weight = weight;
    new_edge->next = graph->adjacency_list[source];
    graph->adjacency_list[source] = new_edge;
    graph->vertex_degrees[source]++;
}

void print_graph(Graph* graph) {
    if (!graph) {
        printf("Graph is NULL\n");
        return;
    }

    printf("Graph with %d vertices:\n", graph->num_vertices);
    for (int i = 0; i < graph->num_vertices; i++) {
        printf("Vertex %d (degree: %d): ", i, graph->vertex_degrees[i]);

        Edge* current = graph->adjacency_list[i];
        if (!current) {
            printf("No edges");
        } else {
            while (current) {
                printf("-> %d(w:%d) ", current->destination, current->weight);
                current = current->next;
            }
        }
        printf("\n");
    }
}

bool is_valid_vertex(Graph* graph, int vertex) {
    return graph && vertex >= 0 && vertex < graph->num_vertices;
}