/*
 * Q55. Set a system resource limit using the setrlimit system call.
 *      The soft limit of RLIMIT_NOFILE is lowered to 100; once lowered,
 *      the soft limit cannot be raised above the hard limit again by an
 *      unprivileged process.
 */
#include <stdio.h>
#include <sys/resource.h>

int main(void) {
    struct rlimit rl;
    if (getrlimit(RLIMIT_NOFILE, &rl) == -1) { perror("getrlimit"); return 1; }
    printf("before: soft = %llu, hard = %llu\n",
           (unsigned long long)rl.rlim_cur, (unsigned long long)rl.rlim_max);

    rl.rlim_cur = 100; /* new soft limit */
    if (setrlimit(RLIMIT_NOFILE, &rl) == -1) { perror("setrlimit"); return 1; }

    if (getrlimit(RLIMIT_NOFILE, &rl) == -1) { perror("getrlimit"); return 1; }
    printf("after : soft = %llu, hard = %llu\n",
           (unsigned long long)rl.rlim_cur, (unsigned long long)rl.rlim_max);
    return 0;
}
