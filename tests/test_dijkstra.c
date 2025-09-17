#include "../include/graph.h"
#include "../include/dijkstra.h"
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

void test_graph_creation() {
    printf("Testing graph creation...\n");

    Graph* graph = create_graph(5);
    assert(graph != NULL);
    assert(graph->num_vertices == 5);

    for (int i = 0; i < 5; i++) {
        assert(graph->adjacency_list[i] == NULL);
        assert(graph->vertex_degrees[i] == 0);
    }

    destroy_graph(graph);
    printf("Graph creation test passed!\n");
}

void test_edge_addition() {
    printf("Testing edge addition...\n");

    Graph* graph = create_graph(3);
    assert(graph != NULL);

    add_edge(graph, 0, 1, 5);
    add_edge(graph, 0, 2, 3);
    add_edge(graph, 1, 2, 2);

    assert(graph->vertex_degrees[0] == 2);
    assert(graph->vertex_degrees[1] == 1);
    assert(graph->vertex_degrees[2] == 0);

    Edge* edge = graph->adjacency_list[0];
    assert(edge != NULL);
    assert((edge->destination == 1 && edge->weight == 5) ||
           (edge->destination == 2 && edge->weight == 3));

    destroy_graph(graph);
    printf("Edge addition test passed!\n");
}

void test_priority_queue() {
    printf("Testing priority queue...\n");

    PriorityQueue* pq = create_priority_queue(5);
    assert(pq != NULL);
    assert(is_empty(pq) == true);

    insert(pq, 0, 10);
    insert(pq, 1, 5);
    insert(pq, 2, 15);
    insert(pq, 3, 3);

    assert(is_empty(pq) == false);
    assert(is_in_queue(pq, 0) == true);
    assert(is_in_queue(pq, 4) == false);

    PQNode min_node = extract_min(pq);
    assert(min_node.vertex == 3);
    assert(min_node.distance == 3);

    decrease_key(pq, 0, 2);
    min_node = extract_min(pq);
    assert(min_node.vertex == 0);
    assert(min_node.distance == 2);

    destroy_priority_queue(pq);
    printf("Priority queue test passed!\n");
}

void test_simple_dijkstra() {
    printf("Testing simple Dijkstra algorithm...\n");

    Graph* graph = create_graph(4);
    add_edge(graph, 0, 1, 1);
    add_edge(graph, 0, 2, 4);
    add_edge(graph, 1, 2, 2);
    add_edge(graph, 1, 3, 5);
    add_edge(graph, 2, 3, 1);

    DijkstraResult result = dijkstra(graph, 0);
    assert(result.success == true);
    assert(result.distances[0] == 0);
    assert(result.distances[1] == 1);
    assert(result.distances[2] == 3);
    assert(result.distances[3] == 4);

    assert(result.parents[0] == -1);
    assert(result.parents[1] == 0);
    assert(result.parents[2] == 1);
    assert(result.parents[3] == 2);

    free_dijkstra_result(result);
    destroy_graph(graph);
    printf("Simple Dijkstra test passed!\n");
}

void test_disconnected_graph() {
    printf("Testing disconnected graph...\n");

    Graph* graph = create_graph(4);
    add_edge(graph, 0, 1, 2);
    add_edge(graph, 2, 3, 3);

    DijkstraResult result = dijkstra(graph, 0);
    assert(result.success == true);
    assert(result.distances[0] == 0);
    assert(result.distances[1] == 2);
    assert(result.distances[2] == INF);
    assert(result.distances[3] == INF);

    free_dijkstra_result(result);
    destroy_graph(graph);
    printf("Disconnected graph test passed!\n");
}

void test_single_target_dijkstra() {
    printf("Testing single target Dijkstra...\n");

    Graph* graph = create_graph(5);
    add_edge(graph, 0, 1, 2);
    add_edge(graph, 0, 2, 4);
    add_edge(graph, 1, 3, 3);
    add_edge(graph, 2, 3, 1);
    add_edge(graph, 3, 4, 2);

    DijkstraResult result = dijkstra_single_target(graph, 0, 4);
    assert(result.success == true);
    assert(result.distances[4] == 7);

    free_dijkstra_result(result);
    destroy_graph(graph);
    printf("Single target Dijkstra test passed!\n");
}

void test_large_graph() {
    printf("Testing large graph performance...\n");

    int size = 10;
    Graph* graph = create_graph(size);

    for (int i = 0; i < size - 1; i++) {
        add_edge(graph, i, i + 1, 1);
    }

    DijkstraResult result = dijkstra(graph, 0);
    assert(result.success == true);
    assert(result.distances[0] == 0);
    assert(result.distances[size - 1] == 9);

    free_dijkstra_result(result);
    destroy_graph(graph);
    printf("Large graph test passed!\n");
}

void test_edge_cases() {
    printf("Testing edge cases...\n");

    Graph* graph = create_graph(1);
    DijkstraResult result = dijkstra(graph, 0);
    assert(result.success == true);
    assert(result.distances[0] == 0);

    free_dijkstra_result(result);
    destroy_graph(graph);

    Graph* null_graph = NULL;
    result = dijkstra(null_graph, 0);
    assert(result.success == false);

    printf("Edge cases test passed!\n");
}

int main() {
    printf("=== Running Dijkstra Algorithm Tests ===\n\n");

    test_graph_creation();
    test_edge_addition();
    test_priority_queue();
    test_simple_dijkstra();
    test_disconnected_graph();
    test_single_target_dijkstra();
    test_large_graph();
    test_edge_cases();

    printf("\n=== All Tests Passed Successfully! ===\n");
    return 0;
}