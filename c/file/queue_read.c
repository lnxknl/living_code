#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#define PORT 12345


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
    char *element = q->elements[q->front];
    q->front = (q->front + 1) % MAX_QUEUE_SIZE;
   q->size--;
    return element;
}

// Get the front element of the queue without removing it
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

        int sockfd, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;

    char buffer[256];
//    sprintf(buffer, "Hello, server!");

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("ERROR opening socket");
        exit(1);
    }

    server = gethostbyname("localhost");
    if (server == NULL) {
        fprintf(stderr,"ERROR, no such host\n");
        exit(0);
    }



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
