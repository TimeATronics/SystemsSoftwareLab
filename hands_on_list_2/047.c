/*
 * Q47. Shared memory operations: write data, attach with SHM_RDONLY and
 *      try to overwrite it, detach and remove the segment.
 *      The overwrite attempt runs in a child process because writing into
 *      a read-only mapping raises SIGSEGV and kills it.
 */
#include <signal.h>
#include <stdio.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void) {
    key_t key = ftok(".", 'S');
    int shmid = shmget(key, 1024, IPC_CREAT | 0666);
    if (shmid == -1) { perror("shmget"); return 1; }

    /* write into shared memory */
    char *p = shmat(shmid, NULL, 0);
    if (p == (void *)-1) { perror("shmat"); return 1; }
    strcpy(p, "data written to shared memory");
    printf("written        : %s\n", p);

    /* detach */
    if (shmdt(p) == -1) { perror("shmdt"); return 1; }
    printf("detached\n");
    fflush(stdout); /* do not let the child inherit buffered output */

    /* attach with SHM_RDONLY and try to overwrite it */
    pid_t pid = fork();
    if (pid == -1) { perror("fork"); return 1; }
    if (pid == 0) {
        char *ro = shmat(shmid, NULL, SHM_RDONLY);
        if (ro == (void *)-1) _exit(1);
        printf("read-only view : %s\n", ro);
        fflush(stdout);
        strcpy(ro, "overwrite attempt"); /* raises SIGSEGV */
        printf("overwrite succeeded (unexpected)\n");
        _exit(0);
    }
    int status;
    wait(&status);
    if (WIFSIGNALED(status))
        printf("overwrite      : failed, killed by signal %d (SIGSEGV = %d)\n",
               WTERMSIG(status), SIGSEGV);
    else
        printf("overwrite      : did not fail\n");

    /* remove */
    if (shmctl(shmid, IPC_RMID, NULL) == -1) { perror("IPC_RMID"); return 1; }
    printf("shared memory removed\n");
    return 0;
}
