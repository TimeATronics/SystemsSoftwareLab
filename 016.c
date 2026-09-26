/*
 * Q16. Mandatory locking.
 *   a. write lock, then b. read lock on the whole file.
 */
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main(void) {
    int fd = open("lock_demo.txt", O_CREAT | O_RDWR, 0644);
    if (fd == -1) { perror("open lock_demo.txt"); return 1; }
    struct flock fl;
    fl.l_whence = SEEK_SET;
    fl.l_start = 0;
    fl.l_len = 0; /* whole file */

    /* a. write lock */
    fl.l_type = F_WRLCK;
    fcntl(fd, F_SETLKW, &fl);
    printf("write lock acquired\n");
    sleep(3);

    /* b. read lock */
    fl.l_type = F_RDLCK;
    fcntl(fd, F_SETLKW, &fl);
    printf("read lock acquired\n");
    sleep(3);

    close(fd);
    return 0;
}
