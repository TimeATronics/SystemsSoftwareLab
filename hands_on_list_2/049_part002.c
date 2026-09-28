/*
 * Q49 (part 2). Protect shared memory from concurrent write access with a
 * binary semaphore. Two children add 10000 each to a shared counter; the
 * final value must be 20000.
 */
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

union semun { int val; struct semid_ds *buf; unsigned short *array; };

int main(void) {
    key_t k1 = ftok(".", 'P');
    key_t k2 = ftok(".", 'Q');

    int shmid = shmget(k1, sizeof(int), IPC_CREAT | 0666);
    if (shmid == -1) { perror("shmget"); return 1; }
    int *counter = shmat(shmid, NULL, 0);
    if (counter == (void *)-1) { perror("shmat"); return 1; }
    *counter = 0;

    int semid = semget(k2, 1, IPC_CREAT | 0666);
    if (semid == -1) { perror("semget"); return 1; }
    union semun arg;
    arg.val = 1;
    semctl(semid, 0, SETVAL, arg);

    struct sembuf lock = {0, -1, 0};   /* P: wait */
    struct sembuf unlock = {0, 1, 0};  /* V: signal */

    for (int i = 0; i < 2; i++) {
        pid_t pid = fork();
        if (pid == -1) { perror("fork"); return 1; }
        if (pid == 0) {
            for (int j = 0; j < 10000; j++) {
                semop(semid, &lock, 1);
                (*counter)++; /* critical section */
                semop(semid, &unlock, 1);
            }
            _exit(0);
        }
    }

    wait(NULL);
    wait(NULL);
    printf("counter = %d (expected 20000)\n", *counter);

    shmdt(counter);
    shmctl(shmid, IPC_RMID, NULL);
    semctl(semid, 0, IPC_RMID);
    return 0;
}
