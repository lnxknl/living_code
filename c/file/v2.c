#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

#define BUFFER_SIZE 1024
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
//        printf("%s ", q->elements[(q->front + i) % MAX_QUEUE_SIZE]);
        system(q->elements[(q->front + i) % MAX_QUEUE_SIZE]);
    }
//    printf("\n");
}


int main(int argc, char *argv[]) {
    int fd, ret;
    char buffer[BUFFER_SIZE];
    struct stat st;
    off_t offset = 0;
    time_t last_mtime = 0;
    int flag = 0;

        char *line = NULL;
    size_t len = 0;
    ssize_t read;

    Queue *q = create_queue();

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    fd = open(argv[1], O_RDONLY);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    while (1) {
        ret = fstat(fd, &st);
        if (ret == -1) {
            perror("fstat");
            exit(EXIT_FAILURE);
        }

//        if (st.st_mtime > last_mtime) {
//            last_mtime = st.st_mtime;

            ret = lseek(fd, 0, SEEK_END);
            if (ret == -1) {
                perror("lseek");
                exit(EXIT_FAILURE);
            }
            if (ret > offset) {
                ret = pread(fd, buffer, BUFFER_SIZE, offset);
		printf("ret : %d\n", ret);
		printf("offset: %d\n", offset);
                if (ret == -1) {
                    perror("pread");
                    exit(EXIT_FAILURE);
                }

//                write(STDOUT_FILENO, buffer, ret);
		char command[512];
		snprintf(command, sizeof(command), "notify-send '%s'", buffer);
		memset(buffer, 0, sizeof(buffer));

//		printf("buff: %s\n",buffer);
		if(flag != 0){
			printf("command: %s\n",command);

        		enqueue(q, command);
        		print_queue(q);
//			system(command);
		}

//    if (line) {
//        free(line);
//    }
			flag = 1;

                offset += ret;

		printf("offset: %d\n", offset);
            }
//        } else {
//            printf("File not changed. Stopping...\n");
        sleep(5);
//		continue;
//            break;
//        }

//        sleep(5);
    }

    close(fd);
    exit(EXIT_SUCCESS);
}
