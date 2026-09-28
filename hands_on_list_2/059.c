/*
 * Q59. Catch signals with the signal system call:
 *   ./bin/059 segv    SIGSEGV  (invalid memory access)
 *   ./bin/059 int     SIGINT   (Ctrl-C)
 *   ./bin/059 fpe     SIGFPE   (arithmetic fault)
 *   ./bin/059 alarm   SIGALRM  raised by alarm()
 *   ./bin/059 itimer  SIGALRM  raised by setitimer(ITIMER_REAL)
 *   ./bin/059 vtalrm  SIGVTALRM raised by setitimer(ITIMER_VIRTUAL)
 *   ./bin/059 prof    SIGPROF  raised by setitimer(ITIMER_PROF)
 *      The handler prints the signal name and exits.
 */
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include <unistd.h>

static void handler(int sig) {
    printf("caught signal %d (%s)\n", sig,
           sig == SIGSEGV ? "SIGSEGV" : sig == SIGINT ? "SIGINT" :
           sig == SIGFPE ? "SIGFPE" : sig == SIGALRM ? "SIGALRM" :
           sig == SIGVTALRM ? "SIGVTALRM" : "SIGPROF");
    fflush(stdout);
    _exit(0);
}

int main(int argc, char **argv) {
    if (argc != 2) {
        printf("usage: %s segv|int|fpe|alarm|itimer|vtalrm|prof\n", argv[0]);
        return 1;
    }

    struct itimerval it;
    it.it_value.tv_sec = 2; /* one-shot after 2 seconds */
    it.it_value.tv_usec = 0;
    it.it_interval.tv_sec = 0;
    it.it_interval.tv_usec = 0;

    if (strcmp(argv[1], "segv") == 0) {
        signal(SIGSEGV, handler);
        raise(SIGSEGV);
    } else if (strcmp(argv[1], "int") == 0) {
        signal(SIGINT, handler);
        raise(SIGINT);
    } else if (strcmp(argv[1], "fpe") == 0) {
        signal(SIGFPE, handler);
        raise(SIGFPE);
    } else if (strcmp(argv[1], "alarm") == 0) {
        signal(SIGALRM, handler);
        alarm(2);
        for (;;) pause();
    } else if (strcmp(argv[1], "itimer") == 0) {
        signal(SIGALRM, handler);
        setitimer(ITIMER_REAL, &it, NULL);
        for (;;) pause();
    } else if (strcmp(argv[1], "vtalrm") == 0) {
        signal(SIGVTALRM, handler);
        setitimer(ITIMER_VIRTUAL, &it, NULL);
    } else if (strcmp(argv[1], "prof") == 0) {
        signal(SIGPROF, handler);
        setitimer(ITIMER_PROF, &it, NULL);
    } else {
        printf("unknown signal: %s\n", argv[1]);
        return 1;
    }

    /* VIRTUAL and PROF count CPU time, so burn CPU until the timer fires */
    for (volatile long i = 0;; i++) (void)i;
}
