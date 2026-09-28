/*
 * Q60. Ignore SIGINT with signal(SIGINT, SIG_IGN), then reset it to the
 *      default action with signal(SIGINT, SIG_DFL). The second raise
 *      terminates the process, which is the default action of SIGINT.
 */
#include <signal.h>
#include <stdio.h>
#include <unistd.h>

int main(void) {
    signal(SIGINT, SIG_IGN); /* ignore Ctrl-C */
    raise(SIGINT);
    printf("SIGINT ignored, still running\n");
    fflush(stdout);

    signal(SIGINT, SIG_DFL); /* back to the default action */
    printf("SIGINT reset to default; the next raise terminates the process\n");
    fflush(stdout);
    raise(SIGINT);

    printf("not reached\n");
    return 0;
}
