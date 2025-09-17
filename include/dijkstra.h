#ifndef DIJKSTRA_H
#define DIJKSTRA_H

#include "graph.h"
#include "priority_queue.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct DijkstraResult {
    int* distances;
    int* parents;
    bool success;
} DijkstraResult;

DijkstraResult dijkstra(Graph* graph, int source);
DijkstraResult dijkstra_single_target(Graph* graph, int source, int target);
void print_distances(DijkstraResult result, int num_vertices);
void print_path(DijkstraResult result, int source, int destination);
void free_dijkstra_result(DijkstraResult result);
bool validate_dijkstra_input(Graph* graph, int source);

#endif