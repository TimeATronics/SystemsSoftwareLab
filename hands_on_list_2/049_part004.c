/*
 * Q49 (part 4). Remove the created semaphore with semctl(IPC_RMID).
 *      Check with: $ ipcs -s
 */
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/sem.h>

int main(void) {
    key_t key = ftok(".", 'C');
    int semid = semget(key, 1, IPC_CREAT | 0666); /* create it if missing */
    if (semid == -1) { perror("semget"); return 1; }

    if (semctl(semid, 0, IPC_RMID) == -1) { perror("IPC_RMID"); return 1; }
    printf("semaphore %d removed\n", semid);
    return 0;
}
