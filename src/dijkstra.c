#include "../include/dijkstra.h"

DijkstraResult dijkstra(Graph* graph, int source) {
    DijkstraResult result = {NULL, NULL, false};

    if (!validate_dijkstra_input(graph, source)) {
        printf("Error: Invalid input for Dijkstra algorithm\n");
        return result;
    }

    int num_vertices = graph->num_vertices;

    result.distances = malloc(num_vertices * sizeof(int));
    result.parents = malloc(num_vertices * sizeof(int));

    if (!result.distances || !result.parents) {
        printf("Error: Memory allocation failed\n");
        free_dijkstra_result(result);
        return result;
    }

    PriorityQueue* pq = create_priority_queue(num_vertices);
    if (!pq) {
        printf("Error: Failed to create priority queue\n");
        free_dijkstra_result(result);
        return result;
    }

    for (int i = 0; i < num_vertices; i++) {
        result.distances[i] = INF;
        result.parents[i] = -1;
    }

    result.distances[source] = 0;

    for (int i = 0; i < num_vertices; i++) {
        insert(pq, i, result.distances[i]);
    }

    while (!is_empty(pq)) {
        PQNode current = extract_min(pq);

        if (current.vertex == -1) {
            break;
        }

        if (current.distance == INF) {
            break;
        }

        Edge* edge = graph->adjacency_list[current.vertex];
        while (edge) {
            int neighbor = edge->destination;
            int weight = edge->weight;
            int new_distance = result.distances[current.vertex] + weight;

            if (new_distance < result.distances[neighbor] &&
                is_in_queue(pq, neighbor)) {
                result.distances[neighbor] = new_distance;
                result.parents[neighbor] = current.vertex;
                decrease_key(pq, neighbor, new_distance);
            }

            edge = edge->next;
        }
    }

    destroy_priority_queue(pq);
    result.success = true;
    return result;
}

DijkstraResult dijkstra_single_target(Graph* graph, int source, int target) {
    DijkstraResult result = {NULL, NULL, false};

    if (!validate_dijkstra_input(graph, source) ||
        !is_valid_vertex(graph, target)) {
        printf("Error: Invalid input for single target Dijkstra\n");
        return result;
    }

    int num_vertices = graph->num_vertices;

    result.distances = malloc(num_vertices * sizeof(int));
    result.parents = malloc(num_vertices * sizeof(int));

    if (!result.distances || !result.parents) {
        printf("Error: Memory allocation failed\n");
        free_dijkstra_result(result);
        return result;
    }

    PriorityQueue* pq = create_priority_queue(num_vertices);
    if (!pq) {
        printf("Error: Failed to create priority queue\n");
        free_dijkstra_result(result);
        return result;
    }

    for (int i = 0; i < num_vertices; i++) {
        result.distances[i] = INF;
        result.parents[i] = -1;
    }

    result.distances[source] = 0;

    for (int i = 0; i < num_vertices; i++) {
        insert(pq, i, result.distances[i]);
    }

    while (!is_empty(pq)) {
        PQNode current = extract_min(pq);

        if (current.vertex == -1) {
            break;
        }

        if (current.vertex == target) {
            break;
        }

        if (current.distance == INF) {
            break;
        }

        Edge* edge = graph->adjacency_list[current.vertex];
        while (edge) {
            int neighbor = edge->destination;
            int weight = edge->weight;
            int new_distance = result.distances[current.vertex] + weight;

            if (new_distance < result.distances[neighbor] &&
                is_in_queue(pq, neighbor)) {
                result.distances[neighbor] = new_distance;
                result.parents[neighbor] = current.vertex;
                decrease_key(pq, neighbor, new_distance);
            }

            edge = edge->next;
        }
    }

    destroy_priority_queue(pq);
    result.success = true;
    return result;
}

void print_distances(DijkstraResult result, int num_vertices) {
    if (!result.success || !result.distances) {
        printf("Error: Invalid result\n");
        return;
    }

    printf("\nShortest distances:\n");
    printf("Vertex\tDistance\n");
    printf("------\t--------\n");

    for (int i = 0; i < num_vertices; i++) {
        printf("%d\t", i);
        if (result.distances[i] == INF) {
            printf("INF\n");
        } else {
            printf("%d\n", result.distances[i]);
        }
    }
}

void print_path(DijkstraResult result, int source, int destination) {
    if (!result.success || !result.parents || !result.distances) {
        printf("Error: Invalid result\n");
        return;
    }

    if (result.distances[destination] == INF) {
        printf("No path from %d to %d\n", source, destination);
        return;
    }

    int path[MAX_VERTICES];
    int path_length = 0;
    int current = destination;

    while (current != -1) {
        path[path_length++] = current;
        current = result.parents[current];
    }

    printf("Path from %d to %d (distance: %d): ",
           source, destination, result.distances[destination]);

    for (int i = path_length - 1; i >= 0; i--) {
        printf("%d", path[i]);
        if (i > 0) {
            printf(" -> ");
        }
    }
    printf("\n");
}

void free_dijkstra_result(DijkstraResult result) {
    if (result.distances) {
        free(result.distances);
    }
    if (result.parents) {
        free(result.parents);
    }
}

bool validate_dijkstra_input(Graph* graph, int source) {
    return graph != NULL && is_valid_vertex(graph, source);
}