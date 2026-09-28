/*
 * Q23. Create an orphan: the parent exits first, so the still-running
 *      child is re-parented to init (PID 1).
 */
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main(void) {
    pid_t pid = fork();
    if (pid == -1) { perror("fork"); return 1; }
    if (pid > 0) return 0;
    sleep(2);
    printf("child: pid=%d ppid=%d\n", getpid(), getppid());
    return 0;
}
