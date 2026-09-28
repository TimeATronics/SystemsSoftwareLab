/*
 * Q32. Send data from the parent process to the child process through a pipe.
 */
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void) {
    int fd[2];
    if (pipe(fd) == -1) { perror("pipe"); return 1; }

    pid_t pid = fork();
    if (pid == -1) { perror("fork"); return 1; }

    if (pid == 0) {
        /* child: read end, write end closed */
        close(fd[1]);
        char buf[64];
        int n = read(fd[0], buf, sizeof buf);
        printf("child received %d bytes: %s\n", n, buf);
        close(fd[0]);
    } else {
        /* parent: write end, read end closed */
        close(fd[0]);
        const char *msg = "message from parent";
        write(fd[1], msg, strlen(msg) + 1);
        close(fd[1]);
        wait(NULL);
    }
    return 0;
}
