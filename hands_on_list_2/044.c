/*
 * Q44. Receive a message from the message queue:
 *   a. with 0 as flag        (blocking, waits for a message)
 *   b. with IPC_NOWAIT       (returns immediately with ENOMSG if empty)
 * Run ./bin/043 first so that part (a) has a message to receive.
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
