#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/types.h>

#define BUFFER_SIZE 1024

int main(int argc, char *argv[]) {
    char message[128];
//    int flag = 0;
//    int value = 42;
    int fd, ret;
    char buffer[BUFFER_SIZE];
    off_t offset = 0;

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
        ret = lseek(fd, 0, SEEK_END);
        if (ret == -1) {
            perror("lseek");
            exit(EXIT_FAILURE);
        }
        if (ret > offset) {
            ret = pread(fd, buffer, BUFFER_SIZE, offset);
            if (ret == -1) {
                perror("pread");
                exit(EXIT_FAILURE);
            }
//            write(STDOUT_FILENO, buffer, ret);
	        sprintf(message,buffer);
		char command[512];
		printf("message: %s\n",message);
//		if(flag != 0)
		snprintf(command, sizeof(command), "notify-send '%s'", message);
		printf("command: %s\n",command);
    system(command);

            offset += ret;
//	    flag = 1;
        }
        sleep(1);
    }

    close(fd);
    exit(EXIT_SUCCESS);
}
