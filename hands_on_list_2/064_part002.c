/*
 * Q64 (ii). Signal SIGSTOP Handling: Create two programs: the first program
 * awaits the SIGSTOP signal, while the second program sends the signal using
 * the kill system call. Determine whether the first program successfully
 * catches the signal or not.
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
