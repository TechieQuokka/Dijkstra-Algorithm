#ifndef GRAPH_H
#define GRAPH_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_VERTICES 1000
#define INF 999999

typedef struct Edge {
    int destination;
    int weight;
    struct Edge* next;
} Edge;

typedef struct Graph {
    int num_vertices;
    Edge** adjacency_list;
    int* vertex_degrees;
} Graph;

Graph* create_graph(int num_vertices);
void destroy_graph(Graph* graph);
void add_edge(Graph* graph, int source, int destination, int weight);
void print_graph(Graph* graph);
bool is_valid_vertex(Graph* graph, int vertex);

#endif