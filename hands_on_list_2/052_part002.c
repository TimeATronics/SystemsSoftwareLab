/*
 * Q52 (part 2). Concurrent server using pthread_create(): every accepted
 *      connection is served by a detached thread. Each thread echoes one
 *      message.
 *      Run: ./bin/052_part002 [port]       (default port 5002)
 *      Connect with: ./bin/051_part002 127.0.0.1 5002
 *      Compile with -pthread.
 */
#include <arpa/inet.h>
#include <netinet/in.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

static void *serve(void *arg) {
    int nsd = *(int *)arg;
    free(arg); /* the descriptor was allocated for this thread */

    char buf[256];
    int n = read(nsd, buf, sizeof buf - 1);
    if (n > 0) buf[n] = '\0';
    printf("thread %lu serving: %s\n", (unsigned long)pthread_self(), buf);
    fflush(stdout);
    write(nsd, buf, n + 1);

    close(nsd);
    return NULL;
}

int main(int argc, char **argv) {
    int port = argc > 1 ? atoi(argv[1]) : 5002;

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
    printf("concurrent (pthread) server on port %d\n", port);
    fflush(stdout);

    for (;;) {
        int *nsd = malloc(sizeof *nsd);
        *nsd = accept(sd, NULL, NULL);
        if (*nsd == -1) { free(nsd); continue; }

        pthread_t tid;
        if (pthread_create(&tid, NULL, serve, nsd) != 0) { perror("pthread_create"); close(*nsd); free(nsd); continue; }
        pthread_detach(tid);
    }
}
