/*
 * Q37 (ii). FIFO Communication (One-Way): Write two programs to enable
 * communication through FIFO using one-way communication.
 */
#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>

int main(void) {
    mknod("fifo1", S_IFIFO | 0666, 0); /* ignore EEXIST on later runs */

    int fd = open("fifo1", O_RDONLY); /* blocks until a writer opens it */
    if (fd == -1) { perror("open fifo1"); return 1; }

    char buf[128];
    int n = read(fd, buf, sizeof buf);
    printf("reader received %d bytes: %s\n", n, buf);

    close(fd);
    return 0;
}
