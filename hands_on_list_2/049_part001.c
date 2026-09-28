/*
 * Q49 (part 1). Rewrite the ticket number creation program using a
 * binary semaphore to protect the read-increment-write critical section.
 * Five children take tickets; the last ticket number must be 5.
 */
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

union semun { int val; struct semid_ds *buf; unsigned short *array; };

int main(void) {
    int fd = open("ticket_sem.db", O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (fd == -1) { perror("open ticket_sem.db"); return 1; }
    write(fd, "0\n", 2);
    close(fd);

    key_t key = ftok(".", 'T');
    int semid = semget(key, 1, IPC_CREAT | 0666);
    if (semid == -1) { perror("semget"); return 1; }
    union semun arg;
    arg.val = 1;
    semctl(semid, 0, SETVAL, arg);

    struct sembuf lock = {0, -1, 0};   /* P: wait */
    struct sembuf unlock = {0, 1, 0};  /* V: signal */

    for (int i = 0; i < 5; i++) {
        pid_t pid = fork();
        if (pid == -1) { perror("fork"); return 1; }
        if (pid == 0) {
            semop(semid, &lock, 1); /* enter critical section */

            int tfd = open("ticket_sem.db", O_RDWR);
            char buf[16];
            int n = read(tfd, buf, sizeof buf - 1);
            buf[n] = '\0';
            int ticket = atoi(buf) + 1;
            lseek(tfd, 0, SEEK_SET);
            int len = snprintf(buf, sizeof buf, "%d\n", ticket);
            write(tfd, buf, len);
            close(tfd);

            printf("child %d got ticket %d\n", i, ticket);
            fflush(stdout);
            semop(semid, &unlock, 1); /* leave critical section */
            _exit(0);
        }
    }

    for (int i = 0; i < 5; i++) wait(NULL);
    printf("all tickets issued (final value in ticket_sem.db is 5)\n");
    return 0;
}
