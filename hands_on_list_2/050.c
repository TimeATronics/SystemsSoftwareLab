/*
 * Q50. Intentionally induce a deadlock with two semaphores: the child
 *      locks semaphore A and waits for B, while the parent locks B and
 *      waits for A. After 5 seconds an alarm prints the confirmation,
 *      kills the child and removes the semaphore set.
 */
#include <signal.h>
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/sem.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

union semun { int val; struct semid_ds *buf; unsigned short *array; };

static int semid;    /* needed inside the signal handler */
static pid_t child;

static void on_alarm(int sig) {
    (void)sig;
    printf("deadlock confirmed: both processes are blocked forever\n");
    fflush(stdout);
    kill(child, SIGKILL);
    semctl(semid, 0, IPC_RMID);
    _exit(0);
}

int main(void) {
    key_t key = ftok(".", 'D');
    semid = semget(key, 2, IPC_CREAT | 0666);
    if (semid == -1) { perror("semget"); return 1; }

    union semun arg;
    arg.val = 1;
    semctl(semid, 0, SETVAL, arg); /* A */
    semctl(semid, 1, SETVAL, arg); /* B */

    signal(SIGALRM, on_alarm);
    alarm(5);

    child = fork();
    if (child == -1) { perror("fork"); return 1; }
    if (child == 0) {
        struct sembuf a = {0, -1, 0}, b = {1, -1, 0};
        semop(semid, &a, 1);
        printf("child: locked A, waiting for B\n"); fflush(stdout);
        sleep(1); /* let the parent lock B first */
        semop(semid, &b, 1);
        _exit(0);
    }

    struct sembuf a = {0, -1, 0}, b = {1, -1, 0};
    semop(semid, &b, 1);
    printf("parent: locked B, waiting for A\n"); fflush(stdout);
    sleep(1); /* child is now holding A */
    semop(semid, &a, 1);

    wait(NULL);
    return 0;
}
