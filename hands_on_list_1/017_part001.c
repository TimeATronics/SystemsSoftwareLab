/*
 * Q17 (part 1). Online ticket reservation: store the starting ticket
 * number in the file and exit.
 */
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

int main(void) {
    int fd = open("ticket.db", O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (fd == -1) { perror("open ticket.db"); return 1; }
    write(fd, "0\n", 2);
    close(fd);
    printf("ticket number stored = 0\n");
    return 0;
}
