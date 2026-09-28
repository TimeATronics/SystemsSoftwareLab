/*
 * Q22. Create a zombie: the child exits, the parent sleeps without calling wait().
 *      Check with: ps -o pid,ppid,state,cmd -p <child-pid>
 */
#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>

int main(void) {
    pid_t pid = fork();
    if (pid == -1) { perror("fork"); return 1; }
    if (pid == 0) _exit(0);
    printf("child: %d (zombie)\n", pid);
    sleep(15);
    return 0;
}
