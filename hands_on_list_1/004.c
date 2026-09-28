/*
 * Q4. Open an existing file with read-write mode, then try O_EXCL.
 *     O_EXCL fails because the file already exists.
 */
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main(void) {
    /* Original File */
    int fd = open("exist.txt", O_CREAT | O_RDWR, 0644);
    if (fd == -1) { perror("open exist.txt"); return 1; } close(fd);
    /* Open it in read-write mode */
    fd = open("exist.txt", O_RDWR);
    if (fd == -1) perror("open exist.txt (O_RDWR)");
    printf("open(exist.txt, O_RDWR) = %d\n", fd); close(fd);
    /* O_CREAT|O_EXCL: create only if absent, otherwise EEXIST */
    fd = open("exist.txt", O_CREAT | O_EXCL | O_RDWR, 0644);
    if (fd == -1) perror("open exist.txt (O_CREAT|O_EXCL)");
    printf("open(exist.txt, O_CREAT|O_EXCL) = %d (fails: file already exists)\n", fd);
    return 0;
}
