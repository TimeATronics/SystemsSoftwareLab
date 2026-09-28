/*
 * Q48. Create a semaphore set and initialise its values:
 *   a. semaphore 0 as a binary semaphore   (value 1)
 *   b. semaphore 1 as a counting semaphore (value 3)
 * Check with: $ ipcs -s
 */
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/sem.h>

union semun { int val; struct semid_ds *buf; unsigned short *array; };

int main(void) {
    key_t key = ftok(".", 'M');
    int semid = semget(key, 2, IPC_CREAT | 0666); /* set of 2 semaphores */
    if (semid == -1) { perror("semget"); return 1; }

    union semun arg;
    arg.val = 1; /* a. binary semaphore */
    if (semctl(semid, 0, SETVAL, arg) == -1) { perror("SETVAL binary"); return 1; }
    arg.val = 3; /* b. counting semaphore */
    if (semctl(semid, 1, SETVAL, arg) == -1) { perror("SETVAL counting"); return 1; }

    printf("semid = %d: sem0(binary) = %d, sem1(counting) = %d\n",
           semid, semctl(semid, 0, GETVAL), semctl(semid, 1, GETVAL));
    return 0;
}
