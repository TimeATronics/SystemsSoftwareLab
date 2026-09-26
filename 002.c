/*
 * Q2. Run a program in an infinite loop in the background.
 *     /proc/<pid>/status, /proc/<pid>/stat and /proc/<pid>/fd.
 */
#include <stdio.h>
#include <unistd.h>

int main(void) {
    printf("pid = %d\n", getpid()); fflush(stdout);
    for (;;) sleep(5);
}
