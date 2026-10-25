/*
 * Q42. Message Queue Information: Write a program to print information about
 * a message queue using msqid_ds and ipc_perm structures:
 *   Access permission
 *   UID, GID
 *   Time of last message sent and received
 *   Time of last change in the message queue
 *   Size of the queue
 *   Number of messages in the queue
 *   Maximum number of bytes allowed
 *   PID of the msgsnd and msgrcv
 */
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <time.h>

int main(void) {
    key_t key = ftok(".", 'A');
    int msqid = msgget(key, IPC_CREAT | 0666);
    if (msqid == -1) { perror("msgget"); return 1; }

    struct msqid_ds ds;
    if (msgctl(msqid, IPC_STAT, &ds) == -1) { perror("IPC_STAT"); return 1; }

    printf("Access permissions     = 0%o\n", ds.msg_perm.mode);
    printf("UID                    = %u\n", ds.msg_perm.uid);
    printf("GID                    = %u\n", ds.msg_perm.gid);
    printf("Last message sent      = %s", ctime(&ds.msg_stime));
    printf("Last message received  = %s", ctime(&ds.msg_rtime));
    printf("Last change in queue   = %s", ctime(&ds.msg_ctime));
    printf("Size of the queue      = %lu bytes\n", (unsigned long)ds.msg_cbytes);
    printf("Number of messages     = %lu\n", (unsigned long)ds.msg_qnum);
    printf("Maximum bytes allowed  = %lu\n", (unsigned long)ds.msg_qbytes);
    printf("PID of last msgsnd     = %d\n", ds.msg_lspid);
    printf("PID of last msgrcv     = %d\n", ds.msg_lrpid);
    return 0;
}
