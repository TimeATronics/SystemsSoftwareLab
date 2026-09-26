/*
 * Q5. Create five files in an infinite loop and run it in the background.
 *     Check the descriptor table with ls -l /proc/<pid>/fd.
 *     Stop it with kill <pid>.
 */
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main(void) {
    printf("pid = %d\n", getpid()); fflush(stdout);
    const char *names[5] = {"five_0.txt", "five_1.txt", "five_2.txt", "five_3.txt", "five_4.txt"};
    for (;;) {
        int fd[5];
        for (int i = 0; i < 5; i++) fd[i] = open(names[i], O_CREAT | O_WRONLY, 0644);
        printf("open fds: %d %d %d %d %d\n", fd[0], fd[1], fd[2], fd[3], fd[4]);
        sleep(10);
        for (int i = 0; i < 5; i++) close(fd[i]);
    }
}
