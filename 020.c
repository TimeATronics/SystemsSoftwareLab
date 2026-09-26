/*
 * Q20. Call fork() and print the parent and child process IDs.
 *      fork() returns 0 in the child and the child's pid in the parent.
 */
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main(void) {
    pid_t pid = fork();
    if (pid == -1) { perror("fork"); return 1; }
    if (pid == 0) printf("child : pid=%d ppid=%d\n", getpid(), getppid());
    else printf("parent: pid=%d child=%d\n", getpid(), pid);
    return 0;
}
