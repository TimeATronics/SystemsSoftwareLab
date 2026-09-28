/*
 * Q30. Run a command after N seconds using a daemon process.
 *   ./bin/030        run the task after 5 seconds
 *   ./bin/030 N      run the task after N seconds
 * The task appends one line to /tmp/030_daemon.log.
 */
#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char **argv) {
    if (fork() != 0) return 0;
    setsid(); chdir("/");
    int n = argc > 1 ? atoi(argv[1]) : 5;
    sleep(n);
    /* Verification log */
    int fd = open("/tmp/030_daemon.log", O_CREAT | O_WRONLY | O_APPEND, 0644);
    if (fd == -1) return 1;
    write(fd, "task executed\n", 14); close(fd);
    return 0;
}
