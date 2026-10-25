/*
 * Q64 (i). Signal SIGSTOP Handling: Create two programs: the first program
 * awaits the SIGSTOP signal, while the second program sends the signal using
 * the kill system call. Determine whether the first program successfully
 * catches the signal or not.
 */
#include <signal.h>
#include <stdio.h>
#include <unistd.h>

static void handler(int sig) {
    printf("handler for signal %d (never called for SIGSTOP)\n", sig);
}

int main(void) {
    signal(SIGSTOP, handler); /* silently has no effect */

    printf("pid = %d: stopping with SIGSTOP, resume with kill -CONT %d\n", getpid(), getpid());
    fflush(stdout);

    raise(SIGSTOP);
    printf("resumed: SIGSTOP was NOT caught (it always stops the process)\n");
    return 0;
}
