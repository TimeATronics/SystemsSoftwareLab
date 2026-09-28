/*
 * Q41. Create a message queue and print the key and the message queue ID.
 *      Check the queue with: $ ipcs -q
 *      Remove it with:       $ ipcrm -q <msqid>
 */
#include <stdio.h>
#include <sys/ipc.h>
#include <sys/msg.h>

int main(void) {
    key_t key = ftok(".", 'A');
    if (key == -1) { perror("ftok"); return 1; }

    int msqid = msgget(key, IPC_CREAT | 0666);
    if (msqid == -1) { perror("msgget"); return 1; }

    printf("key = 0x%x, msqid = %d\n", (unsigned)key, msqid);
    return 0;
}
