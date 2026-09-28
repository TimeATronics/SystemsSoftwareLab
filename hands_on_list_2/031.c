/*
 * Q31. Create a pipe, write into it, read from it and display the content
 *      on the monitor.
 */
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main(void) {
    int fd[2];
    if (pipe(fd) == -1) { perror("pipe"); return 1; }

    const char *msg = "hello through pipe";
    write(fd[1], msg, strlen(msg) + 1); /* write end */

    char buf[64];
    int n = read(fd[0], buf, sizeof buf); /* read end */
    printf("read %d bytes: %s\n", n, buf);

    close(fd[0]);
    close(fd[1]);
    return 0;
}
