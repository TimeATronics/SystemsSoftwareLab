/*
 * Q45. Changing Message Queue Permissions: Write a program to change the
 * existing message queue permissions using the msqid_ds structure.
 */
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>

int main(void) {
    key_t key = ftok(".", 'A');
    int msqid = msgget(key, IPC_CREAT | 0666);
    if (msqid == -1) { perror("msgget"); return 1; }

    struct msqid_ds ds;
    if (msgctl(msqid, IPC_STAT, &ds) == -1) { perror("IPC_STAT"); return 1; }
    printf("old permissions = 0%o\n", ds.msg_perm.mode);

    ds.msg_perm.mode = 0660; /* new permissions */
    if (msgctl(msqid, IPC_SET, &ds) == -1) { perror("IPC_SET"); return 1; }

    if (msgctl(msqid, IPC_STAT, &ds) == -1) { perror("IPC_STAT"); return 1; }
    printf("new permissions = 0%o\n", ds.msg_perm.mode);
    return 0;
}
