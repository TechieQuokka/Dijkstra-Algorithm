#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct PQNode {
    int vertex;
    int distance;
} PQNode;

typedef struct PriorityQueue {
    PQNode* heap;
    int* position;
    int size;
    int capacity;
} PriorityQueue;

PriorityQueue* create_priority_queue(int capacity);
void destroy_priority_queue(PriorityQueue* pq);
bool is_empty(PriorityQueue* pq);
bool is_in_queue(PriorityQueue* pq, int vertex);
void insert(PriorityQueue* pq, int vertex, int distance);
PQNode extract_min(PriorityQueue* pq);
void decrease_key(PriorityQueue* pq, int vertex, int new_distance);
void heapify_up(PriorityQueue* pq, int index);
void heapify_down(PriorityQueue* pq, int index);
void swap_nodes(PriorityQueue* pq, int i, int j);

#endif