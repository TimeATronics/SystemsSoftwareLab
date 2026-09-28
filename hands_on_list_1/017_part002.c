/*
 * Q17 (part 2). Online ticket reservation: take a whole-file write lock,
 * read the ticket number, increment it, write it back and print it.
 */
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(void) {
    int fd = open("ticket.db", O_RDWR);
    if (fd == -1) { perror("open ticket.db"); return 1; }

    struct flock fl;
    fl.l_type = F_WRLCK;
    fl.l_whence = SEEK_SET;
    fl.l_start = 0;
    fl.l_len = 0; /* whole file */
    fcntl(fd, F_SETLKW, &fl);

    char buf[16];
    int n = read(fd, buf, sizeof buf - 1);
    buf[n] = '\0';
    int ticket = atoi(buf) + 1;

    lseek(fd, 0, SEEK_SET);
    int len = snprintf(buf, sizeof buf, "%d\n", ticket);
    write(fd, buf, len);
    printf("new ticket number = %d\n", ticket);

    close(fd); /* close fd and release lock */
    return 0;
}
