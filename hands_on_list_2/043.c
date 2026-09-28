/*
 * Q43. Send a message to the message queue. Check the queue with $ipcs -q.
 *   ./bin/043             sends the default message
 *   ./bin/043 hello       sends "hello"
 */
#include <stdio.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>

struct msg { long mtype; char mtext[128]; };

int main(int argc, char **argv) {
    key_t key = ftok(".", 'A');
    int msqid = msgget(key, IPC_CREAT | 0666);
    if (msqid == -1) { perror("msgget"); return 1; }

    struct msg m;
    m.mtype = 1; /* mtype must be a positive integer */
    const char *text = argc > 1 ? argv[1] : "hello queue";
    snprintf(m.mtext, sizeof m.mtext, "%s", text);

    if (msgsnd(msqid, &m, strlen(m.mtext) + 1, 0) == -1) { perror("msgsnd"); return 1; }
    printf("sent: %s (run ipcs -q to check)\n", m.mtext);
    return 0;
}
