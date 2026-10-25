/*
 * Q38 (ii). FIFO Communication (Two-Way): Write two programs to establish
 * communication through FIFO using two-way communication.
 */
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

int main(void) {
    mknod("fifo_a2b", S_IFIFO | 0666, 0); /* ignore EEXIST on later runs */
    mknod("fifo_b2a", S_IFIFO | 0666, 0);

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
