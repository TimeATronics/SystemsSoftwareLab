/*
 * Q46. Removing Message Queue: Write a program to remove the message queue.
 */
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>

int main(void) {
    key_t key = ftok(".", 'A');
    int msqid = msgget(key, IPC_CREAT | 0666);
    if (msqid == -1) { perror("msgget"); return 1; }

    if (msgctl(msqid, IPC_RMID, NULL) == -1) { perror("IPC_RMID"); return 1; }
    printf("message queue %d removed\n", msqid);
    return 0;
}
