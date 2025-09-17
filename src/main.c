#include "../include/graph.h"
#include "../include/dijkstra.h"
#include <stdio.h>
#include <stdlib.h>

void print_menu() {
    printf("\n=== Dijkstra Algorithm Implementation ===\n");
    printf("1. Create sample graph\n");
    printf("2. Add edge to graph\n");
    printf("3. Print graph\n");
    printf("4. Run Dijkstra (all destinations)\n");
    printf("5. Run Dijkstra (single destination)\n");
    printf("6. Exit\n");
    printf("Choose an option: ");
}

Graph* create_sample_graph() {
    Graph* graph = create_graph(6);
    if (!graph) {
        printf("Failed to create graph\n");
        return NULL;
    }

    add_edge(graph, 0, 1, 4);
    add_edge(graph, 0, 2, 3);
    add_edge(graph, 1, 2, 1);
    add_edge(graph, 1, 3, 2);
    add_edge(graph, 2, 3, 4);
    add_edge(graph, 3, 4, 2);
    add_edge(graph, 4, 5, 6);
    add_edge(graph, 2, 5, 5);

    printf("Sample graph created with 6 vertices and 8 edges\n");
    return graph;
}

void interactive_add_edge(Graph* graph) {
    if (!graph) {
        printf("No graph available. Create a graph first.\n");
        return;
    }

    int source, destination, weight;

    printf("Enter source vertex (0-%d): ", graph->num_vertices - 1);
    if (scanf("%d", &source) != 1) {
        printf("Invalid input\n");
        return;
    }

    printf("Enter destination vertex (0-%d): ", graph->num_vertices - 1);
    if (scanf("%d", &destination) != 1) {
        printf("Invalid input\n");
        return;
    }

    printf("Enter weight: ");
    if (scanf("%d", &weight) != 1) {
        printf("Invalid input\n");
        return;
    }

    add_edge(graph, source, destination, weight);
    printf("Edge added successfully\n");
}

void run_dijkstra_all(Graph* graph) {
    if (!graph) {
        printf("No graph available. Create a graph first.\n");
        return;
    }

    int source;
    printf("Enter source vertex (0-%d): ", graph->num_vertices - 1);
    if (scanf("%d", &source) != 1) {
        printf("Invalid input\n");
        return;
    }

    DijkstraResult result = dijkstra(graph, source);

    if (result.success) {
        print_distances(result, graph->num_vertices);

        char choice;
        printf("\nDo you want to see paths to all vertices? (y/n): ");
        scanf(" %c", &choice);

        if (choice == 'y' || choice == 'Y') {
            for (int i = 0; i < graph->num_vertices; i++) {
                if (i != source) {
                    print_path(result, source, i);
                }
            }
        }

        free_dijkstra_result(result);
    } else {
        printf("Dijkstra algorithm failed\n");
    }
}

void run_dijkstra_single(Graph* graph) {
    if (!graph) {
        printf("No graph available. Create a graph first.\n");
        return;
    }

    int source, target;

    printf("Enter source vertex (0-%d): ", graph->num_vertices - 1);
    if (scanf("%d", &source) != 1) {
        printf("Invalid input\n");
        return;
    }

    printf("Enter target vertex (0-%d): ", graph->num_vertices - 1);
    if (scanf("%d", &target) != 1) {
        printf("Invalid input\n");
        return;
    }

    DijkstraResult result = dijkstra_single_target(graph, source, target);

    if (result.success) {
        printf("\nShortest distance from %d to %d: ", source, target);
        if (result.distances[target] == INF) {
            printf("INF (no path)\n");
        } else {
            printf("%d\n", result.distances[target]);
            print_path(result, source, target);
        }

        free_dijkstra_result(result);
    } else {
        printf("Dijkstra algorithm failed\n");
    }
}

int main() {
    Graph* graph = NULL;
    int choice;

    printf("Welcome to Dijkstra Algorithm Implementation!\n");

    while (1) {
        print_menu();

        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please try again.\n");
            while (getchar() != '\n');
            continue;
        }

        switch (choice) {
            case 1:
                if (graph) {
                    destroy_graph(graph);
                }
                graph = create_sample_graph();
                break;

            case 2:
                interactive_add_edge(graph);
                break;

            case 3:
                if (graph) {
                    print_graph(graph);
                } else {
                    printf("No graph available. Create a graph first.\n");
                }
                break;

            case 4:
                run_dijkstra_all(graph);
                break;

            case 5:
                run_dijkstra_single(graph);
                break;

            case 6:
                printf("Exiting program...\n");
                if (graph) {
                    destroy_graph(graph);
                }
                return 0;

            default:
                printf("Invalid choice. Please try again.\n");
                break;
        }
    }

    return 0;
}