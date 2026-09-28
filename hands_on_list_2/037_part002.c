/*
 * Q37 (part 2). FIFO one-way communication: reader. Opens the FIFO for
 * reading (blocks until the writer arrives), reads one message and
 * displays it.
 * Run in one terminal: ./bin/037_part002
 * Run in another    : ./bin/037_part001
 */
#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>

int main(void) {
    mkfifo("fifo1", 0666); /* ignore EEXIST on later runs */

    int fd = open("fifo1", O_RDONLY); /* blocks until a writer opens it */
    if (fd == -1) { perror("open fifo1"); return 1; }

    char buf[128];
    int n = read(fd, buf, sizeof buf);
    printf("reader received %d bytes: %s\n", n, buf);

    close(fd);
    return 0;
}
