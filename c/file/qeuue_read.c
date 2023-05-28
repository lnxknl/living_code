#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_QUEUE_SIZE 5

// Queue data structure
typedef struct {
    char **elements;
    int front;
    int rear;
    int size;
} Queue;

// Create a new queue
Queue *create_queue() {
    Queue *q = malloc(sizeof(Queue));
    q->elements = malloc(MAX_QUEUE_SIZE * sizeof(char *));
    q->front = 0;
    q->rear = -1;
    q->size = 0;
    return q;
}

// Enqueue an element into the queue
void enqueue(Queue *q, char *element) {
    if (q->size == MAX_QUEUE_SIZE) {
        free(q->elements[q->front]);
        q->front = (q->front + 1) % MAX_QUEUE_SIZE;
        q->size--;
    }
    q->rear = (q->rear + 1) % MAX_QUEUE_SIZE;
    q->elements[q->rear] = strdup(element);
    q->size++;
}

// Dequeue an element from the queue
char *dequeue(Queue *q) {
    if (q->size == 0) {
        return NULL;
    }
    char *element = q->// Get the front element of the queue without removing it
char *front(Queue *q) {
    if (q->size == 0) {
        return NULL;
    }
    return q->elements[q->front];
}

// Print the contents of the queue
void print_queue(Queue *q) {
    printf("Queue contents: ");
    for (int i = 0; i < q->size; i++) {
        printf("%s ", q->elements[(q->front + i) % MAX_QUEUE_SIZE]);
    }
    printf("\n");
}

int main() {
    FILE *fp;
    char *line = NULL;
    size_t len = 0;
    ssize_t read;

    Queue *q = create_queue();

    fp = fopen("input.txt", "r");
    if (fp == NULL) {
        perror("fopen");
        exit(EXIT_FAILURE);
    }

    while ((read = getline(&line, &len, fp)) != -1) {
        enqueue(q, line);
        print_queue(q);
    }

    fclose(fp);
    if (line) {
        free(line);
    }

    return 0;
}

