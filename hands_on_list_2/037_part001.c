/*
 * Q37 (part 1). FIFO one-way communication: writer. Creates the FIFO,
 * opens it for writing (blocks until the reader arrives), sends one
 * message and exits.
 * Run in one terminal: ./bin/037_part002
 * Run in another    : ./bin/037_part001
 */
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

int main(void) {
    mkfifo("fifo1", 0666); /* ignore EEXIST on later runs */

    int fd = open("fifo1", O_WRONLY); /* blocks until a reader opens it */
    if (fd == -1) { perror("open fifo1"); return 1; }

    const char *msg = "message written into FIFO";
    write(fd, msg, strlen(msg) + 1); /* include the terminating NUL */
    printf("writer sent: %s\n", msg);

    close(fd);
    return 0;
}
