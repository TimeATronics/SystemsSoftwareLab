/*
 * Q62. Signal Handling with sigaction: Write a program to ignore a SIGINT
 * signal and then reset it to the default action using the sigaction system
 * call.
 */
#include <signal.h>
#include <stdio.h>
#include <unistd.h>

int main(void) {
    struct sigaction sa;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;

    sa.sa_handler = SIG_IGN; /* ignore Ctrl-C */
    sigaction(SIGINT, &sa, NULL);
    raise(SIGINT);
    printf("SIGINT ignored, still running\n");
    fflush(stdout);

    sa.sa_handler = SIG_DFL; /* back to the default action */
    sigaction(SIGINT, &sa, NULL);
    printf("SIGINT reset to default; the next raise terminates the process\n");
    fflush(stdout);
    raise(SIGINT);

    printf("not reached\n");
    return 0;
}
