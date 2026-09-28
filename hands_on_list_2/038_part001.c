/*
 * Q38 (part 1). FIFO two-way communication: side A. Writes into
 * fifo_a2b first, then reads the reply from fifo_b2a.
 * Run in one terminal: ./bin/038_part002
 * Run in another    : ./bin/038_part001
 */
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

int main(void) {
    mkfifo("fifo_a2b", 0666); /* ignore EEXIST on later runs */
    mkfifo("fifo_b2a", 0666);

    int w = open("fifo_a2b", O_WRONLY); /* blocks until B reads */
    const char *msg = "A to B: hello";
    write(w, msg, strlen(msg) + 1);
    printf("A sent    : %s\n", msg);

    int r = open("fifo_b2a", O_RDONLY); /* blocks until B writes */
    char buf[128];
    int n = read(r, buf, sizeof buf);
    printf("A received: %d bytes: %s\n", n, buf);

    close(w);
    close(r);
    return 0;
}
