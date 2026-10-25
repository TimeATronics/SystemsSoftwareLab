/*
 * Q40. Process File Limit and Pipe Size: Write a program to print the
 * maximum number of files that can be opened within a process and the size
 * of a pipe (circular buffer).
 */
#include <stdio.h>
#include <unistd.h>

int main(void) {
    printf("maximum open files per process (OPEN_MAX) = %ld\n", sysconf(_SC_OPEN_MAX));
    printf("pipe size (PIPE_BUF)                       = %ld\n", pathconf(".", _PC_PIPE_BUF));
    return 0;
}
