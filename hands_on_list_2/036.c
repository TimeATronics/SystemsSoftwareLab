/*
 * Q36. FIFO File Creation: Create a FIFO file using:
 *   mknod command
 *   mkfifo command
 *   Use strace command to determine which command (mknod or mkfifo) is
 *   more efficient.
 *   mknod system call
 *   mkfifo library function
 */
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>

int main(void) {
    /* d. mknod system call */
    unlink("fifo_mknod");
    if (mknod("fifo_mknod", S_IFIFO | 0666, 0) == -1) perror("mknod");

    /* e. mkfifo library function */
    unlink("fifo_mkfifo");
    if (mkfifo("fifo_mkfifo", 0666) == -1) perror("mkfifo");

    printf("created fifo_mknod and fifo_mkfifo\n");
    return 0;
}
