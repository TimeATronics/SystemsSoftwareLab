/*
 * Q63. Creating an Orphan Process: Write a program to create an orphan
 * process. Utilize the kill system call to send a SIGKILL signal from the
 * child process to the parent process.
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
