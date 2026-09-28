/*
 * Q12. Find the opening mode of a file with fcntl(fd, F_GETFL).     
 */
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main(void) {
    int fd = open("mode_demo.txt", O_CREAT | O_RDWR, 0644);
    if (fd == -1) { perror("open mode_demo.txt"); return 1; }
    int flags = fcntl(fd, F_GETFL);
    int mode = flags & O_ACCMODE;
    printf("F_GETFL = 0%o, opening mode = %s\n", flags,
           mode == O_RDONLY ? "O_RDONLY" :
           mode == O_WRONLY ? "O_WRONLY" : "O_RDWR");
    close(fd);
    return 0;
}
