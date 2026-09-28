/*
 * Q54. Print the system resource limits using the getrlimit system call.
 *      Each resource has a soft limit (rlim_cur) and a hard limit
 *      (rlim_max); the value RLIM_INFINITY means unlimited.
 */
#include <stdio.h>
#include <sys/resource.h>

int main(void) {
    struct rlimit rl;

    getrlimit(RLIMIT_CPU, &rl);    printf("CPU time        soft = %llu hard = %llu\n", (unsigned long long)rl.rlim_cur, (unsigned long long)rl.rlim_max);
    getrlimit(RLIMIT_FSIZE, &rl);  printf("file size       soft = %llu hard = %llu\n", (unsigned long long)rl.rlim_cur, (unsigned long long)rl.rlim_max);
    getrlimit(RLIMIT_DATA, &rl);   printf("data segment    soft = %llu hard = %llu\n", (unsigned long long)rl.rlim_cur, (unsigned long long)rl.rlim_max);
    getrlimit(RLIMIT_STACK, &rl);  printf("stack size      soft = %llu hard = %llu\n", (unsigned long long)rl.rlim_cur, (unsigned long long)rl.rlim_max);
    getrlimit(RLIMIT_CORE, &rl);   printf("core file       soft = %llu hard = %llu\n", (unsigned long long)rl.rlim_cur, (unsigned long long)rl.rlim_max);
    getrlimit(RLIMIT_NOFILE, &rl); printf("open files      soft = %llu hard = %llu\n", (unsigned long long)rl.rlim_cur, (unsigned long long)rl.rlim_max);
    getrlimit(RLIMIT_AS, &rl);     printf("address space   soft = %llu hard = %llu\n", (unsigned long long)rl.rlim_cur, (unsigned long long)rl.rlim_max);
    getrlimit(RLIMIT_NPROC, &rl);  printf("processes       soft = %llu hard = %llu\n", (unsigned long long)rl.rlim_cur, (unsigned long long)rl.rlim_max);
    return 0;
}
