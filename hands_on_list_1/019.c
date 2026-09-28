/*
 * Q19. Process states: start the process in the running, sleeping or
 *      stopped state and confirm it with ps / top.
 *   ./bin/019 running : busy loop -> state R
 *   ./bin/019 sleeping : sleeps in a loop -> state S
 *   ./bin/019 stopped : stops itself (SIGSTOP) -> state T
 *   ps -o pid,stat,cmd -p <pid>
 *   kill -CONT <pid>   to resume a stopped process
 */
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char **argv) {
    if (argc != 2) {
        printf("usage: %s running|sleeping|stopped\n", argv[0]);
        return 1;
    }

    printf("pid = %d, state = %s\n", getpid(), argv[1]);
    fflush(stdout);

    if (strcmp(argv[1], "running") == 0) for (;;) ;
    else if (strcmp(argv[1], "sleeping") == 0) for (;;) sleep(5);
    else if (strcmp(argv[1], "stopped") == 0) {
        raise(SIGSTOP);
        printf("resumed with SIGCONT\n");
    }
    else printf("unknown state: %s\n", argv[1]);

    return 0;
}
