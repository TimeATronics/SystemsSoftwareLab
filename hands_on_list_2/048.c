/*
 * Q48. Semaphore Creation and Initialization: Write a program to create a
 * semaphore and initialize its value:
 *   Create a binary semaphore
 *   Create a counting semaphore
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
