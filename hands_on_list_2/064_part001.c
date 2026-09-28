/*
 * Q64 (part 1). Await SIGSTOP. A handler cannot be installed for SIGSTOP
 *      (or SIGKILL): the signal always stops the process, so the handler
 *      is never called.
 *      Run in one terminal: ./bin/064_part001
 *      In another        : ./bin/064_part002 <pid> stop
 *                          ./bin/064_part002 <pid> cont
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
