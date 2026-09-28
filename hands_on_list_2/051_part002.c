/*
 * Q51 (part 2). Inter-machine communication with sockets: TCP client.
 *      Connects to the server, sends one message and prints the reply.
 *      Same machine : ./bin/051_part002 127.0.0.1 5000
 *      Other machine: ./bin/051_part002 <server-ip> 5000
 */
#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

int main(int argc, char **argv) {
    const char *ip = argc > 1 ? argv[1] : "127.0.0.1";
    int port = argc > 2 ? atoi(argv[2]) : 5000;

    int sd = socket(AF_INET, SOCK_STREAM, 0);
    if (sd == -1) { perror("socket"); return 1; }

    struct sockaddr_in serv;
    serv.sin_family = AF_INET;
    serv.sin_addr.s_addr = inet_addr(ip); /* dotted-decimal address only */
    serv.sin_port = htons(port);

    if (connect(sd, (struct sockaddr *)&serv, sizeof serv) == -1) { perror("connect"); return 1; }

    const char *msg = "hello from client";
    write(sd, msg, strlen(msg) + 1);

    char buf[300];
    int n = read(sd, buf, sizeof buf - 1);
    if (n > 0) buf[n] = '\0';
    printf("server replied: %s\n", buf);

    close(sd);
    return 0;
}
