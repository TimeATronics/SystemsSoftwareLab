/*
 * Q52 (part 1). Concurrent server using fork(): every accepted connection
 *      is served by a child process, so several clients are handled at
 *      the same time. Each child echoes one message.
 *      Run: ./bin/052_part001 [port]       (default port 5001)
 *      Connect with: ./bin/051_part002 127.0.0.1 5001
 */
#include <arpa/inet.h>
#include <netinet/in.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

int main(int argc, char **argv) {
    int port = argc > 1 ? atoi(argv[1]) : 5001;

    signal(SIGCHLD, SIG_IGN); /* let finished children be reaped automatically */

    int sd = socket(AF_INET, SOCK_STREAM, 0);
    if (sd == -1) { perror("socket"); return 1; }

    int one = 1;
    setsockopt(sd, SOL_SOCKET, SO_REUSEADDR, &one, sizeof one);

    struct sockaddr_in serv;
    serv.sin_family = AF_INET;
    serv.sin_addr.s_addr = INADDR_ANY;
    serv.sin_port = htons(port);

    if (bind(sd, (struct sockaddr *)&serv, sizeof serv) == -1) { perror("bind"); return 1; }
    if (listen(sd, 10) == -1) { perror("listen"); return 1; }
    printf("concurrent (fork) server on port %d\n", port);
    fflush(stdout);

    for (;;) {
        int nsd = accept(sd, NULL, NULL);
        if (nsd == -1) continue;

        pid_t pid = fork();
        if (pid == -1) { perror("fork"); close(nsd); continue; }
        if (pid == 0) {
            /* child serves the client */
            close(sd);
            char buf[256];
            int n = read(nsd, buf, sizeof buf - 1);
            if (n > 0) buf[n] = '\0';
            printf("child %d serving: %s\n", getpid(), buf);
            fflush(stdout);
            write(nsd, buf, n + 1);
            close(nsd);
            _exit(0);
        }
        close(nsd); /* the parent keeps only the listening socket */
    }
}
