/*
 * Q61. Catch signals with the sigaction system call:
 *   ./bin/061 segv    SIGSEGV
 *   ./bin/061 int     SIGINT
 *   ./bin/061 fpe     SIGFPE
 *      sigaction() is the portable version of signal() and gives control
 *      over the signal mask and flags.
 */
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

static void handler(int sig) {
    printf("sigaction caught signal %d (%s)\n", sig,
           sig == SIGSEGV ? "SIGSEGV" : sig == SIGINT ? "SIGINT" : "SIGFPE");
    fflush(stdout);
    _exit(0);
}

int main(int argc, char **argv) {
    if (argc != 2) {
        printf("usage: %s segv|int|fpe\n", argv[0]);
        return 1;
    }

    struct sigaction sa;
    sa.sa_handler = handler;
    sigemptyset(&sa.sa_mask);
    sa.sa_flags = 0;

    if (strcmp(argv[1], "segv") == 0) {
        sigaction(SIGSEGV, &sa, NULL);
        raise(SIGSEGV);
    } else if (strcmp(argv[1], "int") == 0) {
        sigaction(SIGINT, &sa, NULL);
        raise(SIGINT);
    } else if (strcmp(argv[1], "fpe") == 0) {
        sigaction(SIGFPE, &sa, NULL);
        raise(SIGFPE);
    } else {
        printf("unknown signal: %s\n", argv[1]);
        return 1;
    }
    return 0;
}
