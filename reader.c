
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#define FIFO "/tmp/lab_fifo"

int main(void) {
    char buffer[100];
    int n;

    // Open FIFO for reading
    int fd = open(FIFO, O_RDONLY);

    if (fd == -1) {
        perror("open");
        return 1;
    }

    // Continuously receive messages
    while ((n = read(fd, buffer, sizeof(buffer) - 1)) > 0) {
        buffer[n] = '\0';

        printf("Received: %s", buffer);
        fflush(stdout);

        if (strstr(buffer, "exit") != NULL) {
            break;
        }
    }

    close(fd);

    return 0;
}
