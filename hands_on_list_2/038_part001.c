/*
 * Q38 (i). FIFO Communication (Two-Way): Write two programs to establish
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
