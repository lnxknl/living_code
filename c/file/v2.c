#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#define PORT 12345


#define BUFFER_SIZE 1024
//#define BUFFER_SIZE 256
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
        int sockfd, n;
    struct sockaddr_in serv_addr;
    struct hostent *server;

//    char send_buffer[256];
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

        bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    bcopy((char *)server->h_addr,
         (char *)&serv_addr.sin_addr.s_addr,
         server->h_length);
    serv_addr.sin_port = htons(PORT);



        char *line = NULL;
    size_t len = 0;
//    ssize_t read;

    Queue *q = create_queue();

//    if (argc != 2) {
//        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
//        exit(EXIT_FAILURE);
//    }

    fd = open(argv[1], O_RDONLY);
    if (fd == -1) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    if (connect(sockfd,(struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0) {
        perror("ERROR connecting");
        exit(1);
    }

    while (1) {
        ret = fstat(fd, &st);
        if (ret == -1) {
            perror("fstat");
            exit(EXIT_FAILURE);
        }
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




//		printf("buff: %s\n",buffer);
		if(flag != 0){
			printf("command: %s\n",command);
			printf("buffer: %s\n",buffer);

        		enqueue(q, command);
        		print_queue(q);


    		n = write(sockfd, buffer, strlen(buffer));
		   if (n < 0) {
        printf("ERROR writing to socket");
        exit(1);
		   }

		}
		else
    		n = write(sockfd, "hello", strlen("hello"));
			
//    bzero(buffer,1024);
//    n = read(sockfd, buffer, 1024);
//    if (n < 0) {
//        printf("ERROR reading from socket");
//        exit(1);
//    }
//
//    printf("Client received: %s\n", buffer);

//    bzero(buffer,1024);
//			system(command);

//    if (line) {
//        free(line);
//    }
		flag = 1;
		memset(buffer, 0, sizeof(buffer));

                offset += ret;

		printf("offset: %d\n", offset);
            }
}

    close(fd);
    close(sockfd);
    exit(EXIT_SUCCESS);
}
