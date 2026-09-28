/*
 * Q38 (part 2). FIFO two-way communication: side B. Reads from
 * fifo_a2b first, then writes the reply into fifo_b2a.
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

    int r = open("fifo_a2b", O_RDONLY); /* blocks until A writes */
    char buf[128];
    int n = read(r, buf, sizeof buf);
    printf("B received: %d bytes: %s\n", n, buf);

    int w = open("fifo_b2a", O_WRONLY); /* blocks until A reads */
    const char *msg = "B to A: hi back";
    write(w, msg, strlen(msg) + 1);
    printf("B sent    : %s\n", msg);

    close(r);
    close(w);
    return 0;
}
