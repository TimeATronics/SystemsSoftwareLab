/*
 * Q44. Receiving Messages from Message Queue: Write a program to receive
 * messages from the message queue:
 *   With 0 as a flag
 *   With IPC_NOWAIT as a flag
 */
#include <stdio.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>

struct msg { long mtype; char mtext[128]; };

int main(void) {
    key_t key = ftok(".", 'A');
    int msqid = msgget(key, IPC_CREAT | 0666);
    if (msqid == -1) { perror("msgget"); return 1; }

    struct msg m;

    /* a. flag 0: block until a message is available */
    int n = msgrcv(msqid, &m, sizeof m.mtext, 0, 0);
    if (n == -1) perror("msgrcv (flag 0)");
    else printf("flag 0     : %d bytes, mtype = %ld, mtext = %s\n", n, m.mtype, m.mtext);
    fflush(stdout); /* keep the output order if stderr reports an error next */

    /* b. IPC_NOWAIT: do not block, fail with ENOMSG if the queue is empty */
    n = msgrcv(msqid, &m, sizeof m.mtext, 0, IPC_NOWAIT);
    if (n == -1) perror("msgrcv (IPC_NOWAIT)");
    else printf("IPC_NOWAIT : %d bytes, mtype = %ld, mtext = %s\n", n, m.mtype, m.mtext);
    return 0;
}
