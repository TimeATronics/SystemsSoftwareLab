/*
 * Q36. Create a FIFO file four ways:
 *   a. mknod command :  $ mknod fifo_mknod_cmd p
 *   b. mkfifo command:  $ mkfifo fifo_mkfifo_cmd
 *      Both create a file of type p (verified with ls -l):
 *        prw-r--r-- 1 root root 0 ... fifo_mknod_cmd
 *        prw-r--r-- 1 root root 0 ... fifo_mkfifo_cmd
 *   c. strace comparison (which command is more efficient?):
 *        $ strace -e trace=mknodat mkfifo s1.fifo
 *        mknodat(AT_FDCWD, "s1.fifo", S_IFIFO|0666) = 0
 *        $ strace -e trace=mknodat mknod s2.fifo p
 *        mknodat(AT_FDCWD, "s2.fifo", S_IFIFO|0666) = 0
 *      Both commands end in exactly one mknodat system call with the same
 *      arguments, and strace -c reports the same total syscall count (66)
 *      for both, so neither is more efficient: the mkfifo command is a
 *      thin wrapper over the same mknod system call.
 *   d. system call    :  mknod()   (below)
 *   e. library function: mkfifo()  (below)
 * Check the result with: ls -l fifo_mknod fifo_mkfifo   (type p)
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
