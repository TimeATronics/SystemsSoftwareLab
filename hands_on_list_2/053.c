/*
 * Q53. Interval Timer Programming: Write separate programs for each time
 * domain to set an interval timer for 10 seconds and 10 microseconds.
 *   Use ITIMER_REAL
 *   Use ITIMER_VIRTUAL
 *   Use ITIMER_PROF
 */
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include <unistd.h>

static volatile sig_atomic_t count = 0;

static void on_timer(int sig) {
    printf("%s expiration %d (first after 10 s, then every 10 us)\n",
           sig == SIGALRM ? "SIGALRM" : sig == SIGVTALRM ? "SIGVTALRM" : "SIGPROF", ++count);
    fflush(stdout);
    if (count >= 3) _exit(0);
}

int main(int argc, char **argv) {
    if (argc != 2) {
        printf("usage: %s real|virtual|prof\n", argv[0]);
        return 1;
    }

    struct itimerval it;
    it.it_value.tv_sec = 10;      /* first expiry: 10 seconds        */
    it.it_value.tv_usec = 0;
    it.it_interval.tv_sec = 0;    /* then every 10 microseconds      */
    it.it_interval.tv_usec = 10;

    if (strcmp(argv[1], "real") == 0) {
        signal(SIGALRM, on_timer);
        setitimer(ITIMER_REAL, &it, NULL);
        printf("ITIMER_REAL set: waiting 10 seconds for wall-clock time...\n");
        fflush(stdout);
        for (;;) pause();
    } else if (strcmp(argv[1], "virtual") == 0) {
        signal(SIGVTALRM, on_timer);
        setitimer(ITIMER_VIRTUAL, &it, NULL);
        printf("ITIMER_VIRTUAL set: burning CPU for 10 seconds of user time...\n");
        fflush(stdout);
    } else if (strcmp(argv[1], "prof") == 0) {
        signal(SIGPROF, on_timer);
        setitimer(ITIMER_PROF, &it, NULL);
        printf("ITIMER_PROF set: burning CPU for 10 seconds of user+system time...\n");
        fflush(stdout);
    } else {
        printf("unknown timer: %s\n", argv[1]);
        return 1;
    }

    /* VIRTUAL and PROF count CPU time, so the process must keep running */
    while (count < 3) {
        volatile long x = 0;
        for (long i = 0; i < 5000000; i++) x += i;
    }
    return 0;
}
