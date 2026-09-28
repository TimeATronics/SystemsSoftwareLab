/*
 * Q34. Execute ls -l | wc with three different redirection tricks:
 *   a. dup()    b. dup2()    c. fcntl(F_DUPFD)
 * For each variant the parent forks two children connected by a pipe:
 * the first execs ls -l, the second execs wc.
 */
#include <fcntl.h>
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void) {
    const char *names[3] = {"dup", "dup2", "fcntl"};

    for (int i = 0; i < 3; i++) {
        printf("===== ls -l | wc using %s =====\n", names[i]);
        fflush(stdout);

        int fd[2];
        if (pipe(fd) == -1) { perror("pipe"); return 1; }

        pid_t pid = fork();
        if (pid == -1) { perror("fork"); return 1; }
        if (pid == 0) {
            /* first child: ls -l, stdout goes into the pipe */
            if (i == 0) {
                close(fd[0]);
                close(1);
                dup(fd[1]);
                close(fd[1]);
            } else if (i == 1) {
                dup2(fd[1], 1);
                close(fd[0]);
                close(fd[1]);
            } else {
                close(fd[0]);
                close(1);
                int nfd = fcntl(fd[1], F_DUPFD, 0); /* lowest free = 1 */
                close(fd[1]);
                if (nfd != 1) _exit(1);
            }
            execlp("ls", "ls", "-l", (char *)0);
            perror("execlp ls");
            _exit(1);
        }

        pid = fork();
        if (pid == -1) { perror("fork"); return 1; }
        if (pid == 0) {
            /* second child: wc, stdin comes from the pipe */
            if (i == 0) {
                close(fd[1]);
                close(0);
                dup(fd[0]);
                close(fd[0]);
            } else if (i == 1) {
                dup2(fd[0], 0);
                close(fd[0]);
                close(fd[1]);
            } else {
                close(fd[1]);
                close(0);
                int nfd = fcntl(fd[0], F_DUPFD, 0); /* lowest free = 0 */
                close(fd[0]);
                if (nfd != 0) _exit(1);
            }
            execlp("wc", "wc", (char *)0);
            perror("execlp wc");
            _exit(1);
        }

        close(fd[0]);
        close(fd[1]);
        wait(NULL);
        wait(NULL);
    }
    return 0;
}
