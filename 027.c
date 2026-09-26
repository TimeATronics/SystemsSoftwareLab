/*
 * Q27. Write a program to get maximum and minimum real time priority.
 */
#include <stdio.h>
#include <sched.h>

int main(void) {
    printf("SCHED_FIFO: min = %d, max = %d\n",
           sched_get_priority_min(SCHED_FIFO), sched_get_priority_max(SCHED_FIFO));
    printf("SCHED_RR  : min = %d, max = %d\n",
           sched_get_priority_min(SCHED_RR), sched_get_priority_max(SCHED_RR));
    return 0;
}
