/*
 * Q26. Execute ls -Rl with each member of the exec family:
 *      execl, execlp, execle, execv, execvp.
 *      The parent forks a child for each variant and waits for it.
 */
#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>

int main(void) {
    const char *names[5] = {"execl", "execlp", "execle", "execv", "execvp"};

    for (int i = 0; i < 5; i++) {
        printf("===== %s =====\n", names[i]);
        fflush(stdout);

        pid_t pid = fork();
        if (pid == -1) { perror("fork"); return 1; }
        if (pid == 0) {
            /* child */
            if (i == 0)
                execl("/bin/ls", "ls", "-Rl", (char *)0);
            else if (i == 1)
                execlp("ls", "ls", "-Rl", (char *)0);
            else if (i == 2) {
                char *envp[] = {"PATH=/bin:/usr/bin", (char *)0};
                execle("/bin/ls", "ls", "-Rl", (char *)0, envp);
            } else if (i == 3) {
                char *args[] = {"ls", "-Rl", (char *)0};
                execv("/bin/ls", args);
            } else {
                char *args[] = {"ls", "-Rl", (char *)0};
                execvp("ls", args);
            }
            perror(names[i]);
            _exit(1);
        }
        wait(NULL);
    }
    return 0;
}
