/*
 * Q56. Measure the time taken to execute 100 getppid() system calls
 *      using the time stamp counter (rdtsc), which counts processor
 *      cycles since reset.
 */
#include <stdio.h>
#include <unistd.h>

int main(void) {
    unsigned lo, hi;
    __asm__ __volatile__("rdtsc" : "=a"(lo), "=d"(hi));
    unsigned long long start = ((unsigned long long)hi << 32) | lo;

    for (int i = 0; i < 100; i++) getppid();

    __asm__ __volatile__("rdtsc" : "=a"(lo), "=d"(hi));
    unsigned long long end = ((unsigned long long)hi << 32) | lo;

    printf("100 getppid() calls took %llu cycles\n", end - start);
    printf("average = %llu cycles per call\n", (end - start) / 100);
    return 0;
}
