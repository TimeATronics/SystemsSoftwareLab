/*
 * Q64 (part 2). Send SIGSTOP or SIGCONT with the kill system call:
 *      ./bin/064_part002 <pid>        sends SIGSTOP
 *      ./bin/064_part002 <pid> cont   sends SIGCONT
 */
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv) {
    if (argc < 2) {
        printf("usage: %s <pid> [cont]\n", argv[0]);
        return 1;
    }

    int pid = atoi(argv[1]);
    int sig = (argc > 2 && strcmp(argv[2], "cont") == 0) ? SIGCONT : SIGSTOP;

    if (kill(pid, sig) == -1) { perror("kill"); return 1; }
    printf("sent %s to pid %d\n", sig == SIGSTOP ? "SIGSTOP" : "SIGCONT", pid);
    return 0;
}
