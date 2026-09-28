/*
 * Q33. Two-way communication between the parent and the child using two
 *      pipes: pipe1 for parent to child and pipe2 for child to parent.
 */
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void) {
    int p2c[2], c2p[2];
    if (pipe(p2c) == -1 || pipe(c2p) == -1) { perror("pipe"); return 1; }

    pid_t pid = fork();
    if (pid == -1) { perror("fork"); return 1; }

    if (pid == 0) {
        /* child: read from p2c, write into c2p */
        close(p2c[1]);
        close(c2p[0]);
        char buf[64];
        int n = read(p2c[0], buf, sizeof buf);
        printf("child received %d bytes: %s\n", n, buf);
        const char *reply = "hello parent, child here";
        write(c2p[1], reply, strlen(reply) + 1);
        close(p2c[0]);
        close(c2p[1]);
    } else {
        /* parent: write into p2c, read from c2p */
        close(p2c[0]);
        close(c2p[1]);
        const char *msg = "hello child, parent here";
        write(p2c[1], msg, strlen(msg) + 1);
        char buf[64];
        int n = read(c2p[0], buf, sizeof buf);
        printf("parent received %d bytes: %s\n", n, buf);
        close(p2c[1]);
        close(c2p[0]);
        wait(NULL);
    }
    return 0;
}
