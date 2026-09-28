/*
 * Q63. Create an orphan process: the child sends SIGKILL to the parent
 *      with the kill system call, so the still-running child is
 *      re-parented to init (PID 1).
 */
#include <signal.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main(void) {
    pid_t pid = fork();
    if (pid == -1) { perror("fork"); return 1; }

    if (pid == 0) {
        sleep(2);
        kill(getppid(), SIGKILL); /* parent dies now */
        sleep(1);                 /* let the re-parenting happen */
        printf("child : pid=%d, new ppid=%d\n", getpid(), getppid());
        return 0;
    }

    printf("parent: pid=%d, child %d will kill me shortly\n", getpid(), pid);
    fflush(stdout);
    sleep(10);
    printf("parent: not reached\n"); /* the child kills the parent first */
    return 0;
}
