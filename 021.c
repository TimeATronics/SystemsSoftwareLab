/*
 * Q21. Open a file, call fork(), and write to the file from both the
 *      child and the parent. Both share the same open file descriptor,
 *      so they share the file offset.
 */
#include <fcntl.h>
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main(void) {
    int fd = open("fork_write.txt", O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (fd == -1) { perror("open fork_write.txt"); return 1; }
    pid_t pid = fork();
    if (pid == -1) { perror("fork"); close(fd); return 1; }

    if (pid == 0) {
        if (write(fd, "child wrote\n", 12) == -1) perror("child write");
    } else {
        sleep(1);
        if (write(fd, "parent wrote\n", 13) == -1) perror("parent write");
    }

    close(fd);
    printf("see fork_write.txt\n");
    return 0;
}
