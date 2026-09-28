/*
 * Q51 (part 1). Inter-machine communication with sockets: TCP server.
 *      Creates a socket, binds it to a port, waits for one client,
 *      reads a message, echoes it back and exits.
 *      Run: ./bin/051_part001 [port]        (default port 5000)
 */
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

int main(int argc, char **argv) {
    int port = argc > 1 ? atoi(argv[1]) : 5000;

    int sd = socket(AF_INET, SOCK_STREAM, 0); /* TCP socket */
    if (sd == -1) { perror("socket"); return 1; }

    int one = 1; /* reuse the address after a restart */
    setsockopt(sd, SOL_SOCKET, SO_REUSEADDR, &one, sizeof one);

    struct sockaddr_in serv;
    serv.sin_family = AF_INET;
    serv.sin_addr.s_addr = INADDR_ANY; /* any local interface */
    serv.sin_port = htons(port);

    if (bind(sd, (struct sockaddr *)&serv, sizeof serv) == -1) { perror("bind"); return 1; }
    if (listen(sd, 5) == -1) { perror("listen"); return 1; }
    printf("server listening on port %d\n", port);
    fflush(stdout);

    struct sockaddr_in cli;
    socklen_t len = sizeof cli;
    int nsd = accept(sd, (struct sockaddr *)&cli, &len); /* blocks for a client */
    if (nsd == -1) { perror("accept"); return 1; }

    char buf[256];
    int n = read(nsd, buf, sizeof buf - 1);
    if (n > 0) buf[n] = '\0';
    printf("client %s:%d sent: %s\n", inet_ntoa(cli.sin_addr), ntohs(cli.sin_port), buf);

    char reply[300];
    int m = snprintf(reply, sizeof reply, "server got: %s", buf);
    write(nsd, reply, m + 1);

    close(nsd);
    close(sd);
    return 0;
}
