/*
 * Q60. Ignoring and Resetting Signals: Write a program to ignore a SIGINT
 * signal and then reset it to the default action using the signal system
 * call.
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
