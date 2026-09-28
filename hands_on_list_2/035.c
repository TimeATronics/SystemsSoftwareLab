/*
 * Q35. Find the number of directories in the current directory with
 *      ls -l | grep ^d | wc, using only dup2() for the redirection.
 *      Three children share two pipes: ls -> grep -> wc.
 */
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void) {
    int p1[2], p2[2];
    if (pipe(p1) == -1 || pipe(p2) == -1) { perror("pipe"); return 1; }

    /* ls -l : stdout -> p1 */
    pid_t pid = fork();
    if (pid == -1) { perror("fork"); return 1; }
    if (pid == 0) {
        dup2(p1[1], 1);
        close(p1[0]); close(p1[1]); close(p2[0]); close(p2[1]);
        execlp("ls", "ls", "-l", (char *)0);
        perror("execlp ls");
        _exit(1);
    }

    /* grep ^d : stdin <- p1, stdout -> p2 */
    pid = fork();
    if (pid == -1) { perror("fork"); return 1; }
    if (pid == 0) {
        dup2(p1[0], 0);
        dup2(p2[1], 1);
        close(p1[0]); close(p1[1]); close(p2[0]); close(p2[1]);
        execlp("grep", "grep", "^d", (char *)0);
        perror("execlp grep");
        _exit(1);
    }

    /* wc -l : stdin <- p2 */
    pid = fork();
    if (pid == -1) { perror("fork"); return 1; }
    if (pid == 0) {
        dup2(p2[0], 0);
        close(p1[0]); close(p1[1]); close(p2[0]); close(p2[1]);
        execlp("wc", "wc", "-l", (char *)0);
        perror("execlp wc");
        _exit(1);
    }

    close(p1[0]); close(p1[1]);
    close(p2[0]); close(p2[1]);
    wait(NULL); wait(NULL); wait(NULL);
    return 0;
}
