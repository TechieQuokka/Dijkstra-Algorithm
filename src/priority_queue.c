#include "../include/priority_queue.h"

PriorityQueue* create_priority_queue(int capacity) {
    if (capacity <= 0) {
        printf("Error: Invalid capacity\n");
        return NULL;
    }

    PriorityQueue* pq = malloc(sizeof(PriorityQueue));
    if (!pq) {
        printf("Error: Memory allocation failed for priority queue\n");
        return NULL;
    }

    pq->heap = malloc(capacity * sizeof(PQNode));
    if (!pq->heap) {
        printf("Error: Memory allocation failed for heap\n");
        free(pq);
        return NULL;
    }

    pq->position = malloc(capacity * sizeof(int));
    if (!pq->position) {
        printf("Error: Memory allocation failed for position array\n");
        free(pq->heap);
        free(pq);
        return NULL;
    }

    pq->size = 0;
    pq->capacity = capacity;

    for (int i = 0; i < capacity; i++) {
        pq->position[i] = -1;
    }

    return pq;
}

void destroy_priority_queue(PriorityQueue* pq) {
    if (!pq) return;

    free(pq->heap);
    free(pq->position);
    free(pq);
}

bool is_empty(PriorityQueue* pq) {
    return !pq || pq->size == 0;
}

bool is_in_queue(PriorityQueue* pq, int vertex) {
    if (!pq || vertex < 0 || vertex >= pq->capacity) {
        return false;
    }
    return pq->position[vertex] != -1;
}

void swap_nodes(PriorityQueue* pq, int i, int j) {
    if (!pq || i < 0 || j < 0 || i >= pq->size || j >= pq->size) {
        return;
    }

    pq->position[pq->heap[i].vertex] = j;
    pq->position[pq->heap[j].vertex] = i;

    PQNode temp = pq->heap[i];
    pq->heap[i] = pq->heap[j];
    pq->heap[j] = temp;
}

void heapify_up(PriorityQueue* pq, int index) {
    if (!pq || index <= 0) return;

    int parent = (index - 1) / 2;

    if (pq->heap[index].distance < pq->heap[parent].distance) {
        swap_nodes(pq, index, parent);
        heapify_up(pq, parent);
    }
}

void heapify_down(PriorityQueue* pq, int index) {
    if (!pq || index < 0 || index >= pq->size) return;

    int left = 2 * index + 1;
    int right = 2 * index + 2;
    int smallest = index;

    if (left < pq->size &&
        pq->heap[left].distance < pq->heap[smallest].distance) {
        smallest = left;
    }

    if (right < pq->size &&
        pq->heap[right].distance < pq->heap[smallest].distance) {
        smallest = right;
    }

    if (smallest != index) {
        swap_nodes(pq, index, smallest);
        heapify_down(pq, smallest);
    }
}

void insert(PriorityQueue* pq, int vertex, int distance) {
    if (!pq) {
        printf("Error: Priority queue is NULL\n");
        return;
    }

    if (pq->size >= pq->capacity) {
        printf("Error: Priority queue is full\n");
        return;
    }

    if (vertex < 0 || vertex >= pq->capacity) {
        printf("Error: Invalid vertex\n");
        return;
    }

    if (is_in_queue(pq, vertex)) {
        printf("Error: Vertex already in queue\n");
        return;
    }

    int index = pq->size;
    pq->heap[index].vertex = vertex;
    pq->heap[index].distance = distance;
    pq->position[vertex] = index;
    pq->size++;

    heapify_up(pq, index);
}

PQNode extract_min(PriorityQueue* pq) {
    PQNode invalid_node = {-1, -1};

    if (is_empty(pq)) {
        printf("Error: Priority queue is empty\n");
        return invalid_node;
    }

    PQNode min_node = pq->heap[0];
    pq->position[min_node.vertex] = -1;

    pq->size--;
    if (pq->size > 0) {
        pq->heap[0] = pq->heap[pq->size];
        pq->position[pq->heap[0].vertex] = 0;
        heapify_down(pq, 0);
    }

    return min_node;
}

void decrease_key(PriorityQueue* pq, int vertex, int new_distance) {
    if (!pq) {
        printf("Error: Priority queue is NULL\n");
        return;
    }

    if (!is_in_queue(pq, vertex)) {
        printf("Error: Vertex not in queue\n");
        return;
    }

    int index = pq->position[vertex];
    if (new_distance > pq->heap[index].distance) {
        printf("Error: New distance is greater than current distance\n");
        return;
    }

    pq->heap[index].distance = new_distance;
    heapify_up(pq, index);
}