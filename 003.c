/*
 * Q3. Create a file and print its file descriptor value using creat().
 */
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main(void) {
    int fd = creat("creat_demo.txt", 0644);
    if (fd == -1) { perror("creat creat_demo.txt"); return 1; }
    printf("fd = %d\n", fd); close(fd);
    return 0;
}
