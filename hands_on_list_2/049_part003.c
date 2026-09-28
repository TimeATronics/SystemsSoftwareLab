/*
 * Q49 (part 3). Protect two pseudo resources with a counting semaphore
 * initialised to 2: four children each use a resource, at most two may
 * be inside the critical section at the same time.
 */
#include <stdio.h>
#include <stdlib.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

union semun { int val; struct semid_ds *buf; unsigned short *array; };

int main(void) {
    key_t key = ftok(".", 'C');
    int semid = semget(key, 1, IPC_CREAT | 0666);
    if (semid == -1) { perror("semget"); return 1; }
    union semun arg;
    arg.val = 2; /* two resources */
    semctl(semid, 0, SETVAL, arg);

    struct sembuf lock = {0, -1, 0};   /* P: take a resource */
    struct sembuf unlock = {0, 1, 0};  /* V: release it       */

    for (int i = 0; i < 4; i++) {
        pid_t pid = fork();
        if (pid == -1) { perror("fork"); return 1; }
        if (pid == 0) {
            semop(semid, &lock, 1);
            printf("child %d using a resource (free = %d)\n", i, semctl(semid, 0, GETVAL));
            fflush(stdout);
            sleep(1); /* pretend to work with the resource */
            semop(semid, &unlock, 1);
            _exit(0);
        }
    }

    for (int i = 0; i < 4; i++) wait(NULL);
    printf("all children done (free = %d)\n", semctl(semid, 0, GETVAL));
    semctl(semid, 0, IPC_RMID);
    return 0;
}
