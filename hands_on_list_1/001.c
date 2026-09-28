/*
 * Q1. Create the following types of files using (i) shell command (ii) system call
 *   a. soft link: ln -s target.txt soft.link   -> symlink()
 *   b. hard link: ln    target.txt hard.link   -> link()
 *   c. FIFO:      mkfifo my.fifo               -> mknod()
 */
#include <fcntl.h>
#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>

int main(void) {
    /* Original File */
    int fd = open("target.txt", O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (fd == -1) { perror("open target.txt"); return 1; }
    write(fd, "hello\n", 6); close(fd);
    /* a. Soft Link */
    if (symlink("target.txt", "soft.link") == -1) perror("symlink");
    /* b. Hard Link */
    if (link("target.txt", "hard.link") == -1) perror("link");
    /* c. FIFO */
    if (mknod("my.fifo", S_IFIFO | 0666, 0) == -1) perror("mknod");
    return 0;
}
