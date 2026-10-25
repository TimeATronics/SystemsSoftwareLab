/*
 * Q51 (ii). Inter-Machine Communication using Socket: Write a program to
 * communicate between two machines using sockets.
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
