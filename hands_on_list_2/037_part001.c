/*
 * Q37 (i). FIFO Communication (One-Way): Write two programs to enable
 * communication through FIFO using one-way communication.
 */
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

int main(void) {
    mknod("fifo1", S_IFIFO | 0666, 0); /* ignore EEXIST on later runs */

    int fd = open("fifo1", O_WRONLY); /* blocks until a reader opens it */
    if (fd == -1) { perror("open fifo1"); return 1; }

    const char *msg = "message written into FIFO";
    write(fd, msg, strlen(msg) + 1); /* include the terminating NUL */
    printf("writer sent: %s\n", msg);

    close(fd);
    return 0;
}
