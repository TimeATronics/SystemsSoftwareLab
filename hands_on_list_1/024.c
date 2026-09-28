/*
 * Q24. Create three children. The parent waits for one specific child
 *      with waitpid(), then reaps the other two.
 */
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void) {
    pid_t p[3];
    for (int i = 0; i < 3; i++) {
        p[i] = fork();
        if (p[i] == -1) { perror("fork"); return 1; }
        if (p[i] == 0) {
            printf("child %d: pid=%d\n", i, getpid());
            sleep(i + 1);
            _exit(i); /* exit status = child number */
        }
    }

    int status;
    if (waitpid(p[1], &status, 0) == -1) { perror("waitpid"); return 1; }
    printf("parent waited for child 1, exit status = %d\n", WEXITSTATUS(status));

    waitpid(p[0], NULL, 0);
    waitpid(p[2], NULL, 0);
    return 0;
}
