/*
 * Q39. Wait for data to be written into a FIFO within 10 seconds using
 *      select(). The program forks a writer that sends after 2 seconds,
 *      so it can be run on its own. The reader opens the FIFO in
 *      O_NONBLOCK mode and selects on it with a 10 second timeout.
 */
#include <fcntl.h>
#include <stdio.h>
#include <string.h>
#include <sys/select.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void) {
    mkfifo("fifo_sel", 0666); /* ignore EEXIST on later runs */

    pid_t pid = fork();
    if (pid == -1) { perror("fork"); return 1; }
    if (pid == 0) {
        /* writer: sends after 2 seconds */
        sleep(2);
        int w = open("fifo_sel", O_WRONLY);
        if (w == -1) _exit(1);
        write(w, "ping", 5);
        close(w);
        _exit(0);
    }

    int fd = open("fifo_sel", O_RDONLY | O_NONBLOCK);
    if (fd == -1) { perror("open fifo_sel"); return 1; }

    fd_set set;
    struct timeval tv = {10, 0};
    FD_ZERO(&set);
    FD_SET(fd, &set);

    printf("waiting up to 10 seconds for FIFO data...\n");
    int r = select(fd + 1, &set, NULL, NULL, &tv);
    if (r > 0) {
        char buf[32];
        int n = read(fd, buf, sizeof buf);
        printf("data available after %d byte(s): %s\n", n, buf);
    } else {
        printf("no data available within 10 seconds\n");
    }

    close(fd);
    wait(NULL);
    return 0;
}
