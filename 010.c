/*
 * Q10. Open a file in RDWR mode, write 10 bytes, seek 10 bytes forward with lseek
 * and write 10 bytes again.
 * (a) Check the return value of lseek.
 * (b) Examine empty space between data with "od -c seek_demo.txt".
 */
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main(void) {
    int fd = open("seek_demo.txt", O_CREAT | O_RDWR | O_TRUNC, 0644);
    if (fd == -1) { perror("open seek_demo.txt"); return 1; }
    write(fd, "ABCDEFGHIJ", 10);
    off_t pos = lseek(fd, 10, SEEK_CUR);
    printf("lseek return value = %ld\n", (long)pos);
    write(fd, "abcdefghij", 10); close(fd);
    return 0;
}
