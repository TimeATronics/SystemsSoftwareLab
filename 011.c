/*
 * Q11. Open a file, duplicate its descriptor with dup(), dup2() and
 *      fcntl(F_DUPFD), then append through both descriptors for each subpart.
 */
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main(void) {
    int fd = open("dup_demo.txt", O_CREAT | O_WRONLY | O_APPEND, 0644);
    if (fd == -1) { perror("open dup_demo.txt"); return 1; }
    int fd_dup = dup(fd);
    int fd_dup2 = dup2(fd, 9);
    int fd_fcntl = fcntl(fd, F_DUPFD, 10);
    write(fd, "via original\n", 13);
    write(fd_dup, "via dup\n", 8);
    write(fd_dup2, "via dup2\n", 9);
    write(fd_fcntl, "via fcntl\n", 10);
    close(fd);
    close(fd_dup);
    close(fd_dup2);
    close(fd_fcntl);
    printf("FDs: %d %d %d %d\n", fd, fd_dup, fd_dup2, fd_fcntl);
    return 0;
}
