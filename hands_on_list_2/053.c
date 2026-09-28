/*
 * Q53. Set an interval timer for 10 seconds and 10 microseconds in each
 *      time domain:
 *   ./bin/053 real     ITIMER_REAL    -> SIGALRM   (wall-clock time)
 *   ./bin/053 virtual  ITIMER_VIRTUAL -> SIGVTALRM (user CPU time)
 *   ./bin/053 prof     ITIMER_PROF    -> SIGPROF   (user + system CPU time)
 *      The first expiry is after 10 seconds; the reload interval is 10
 *      microseconds. The handler prints each expiry and exits after 3.
 *      For VIRTUAL and PROF the 10 seconds are CPU time, so the wall
 *      time can be longer on a machine that is not fully available.
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
