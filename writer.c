
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <errno.h>

#define FIFO "/tmp/lab_fifo"

int main(void) {
    char message[100];

    // Create the named pipe
    if (mkfifo(FIFO, 0666) == -1 && errno != EEXIST) {
        perror("mkfifo");
        return 1;
    }

    // Open FIFO for writing
    int fd = open(FIFO, O_WRONLY);

    if (fd == -1) {
        perror("open");
        return 1;
    }

    // Keep accepting messages
    while (1) {
        printf("Enter message: ");
        fflush(stdout);

        if (fgets(message, sizeof(message), stdin) == NULL) {
            break;
        }

        // Send message to reader
        size_t len = strlen(message);

        if (write(fd, message, len) == -1) {
            perror("write");
            break;
        }

        // Stop when user enters exit
        if (strcmp(message, "exit\n") == 0) {
            break;
        }
    }

    // Close FIFO
    close(fd);

    return 0;
}
