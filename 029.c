/*
 * Q29. Write a program to get scheduling policy and modify the scheduling policy
 *      (SCHED_FIFO, SCHED_RR).
 */
#include <stdio.h>
#include <sched.h>

int main(void) {
    int p = sched_getscheduler(0);
    printf("current policy = %s\n",
           p == SCHED_FIFO ? "SCHED_FIFO" :
           p == SCHED_RR ? "SCHED_RR" : "SCHED_OTHER");

    struct sched_param sp;
    sp.sched_priority = sched_get_priority_min(SCHED_RR);
    sched_setscheduler(0, SCHED_RR, &sp);

    p = sched_getscheduler(0);
    printf("after sched_setscheduler(SCHED_RR) = %s\n",
           p == SCHED_FIFO ? "SCHED_FIFO" :
           p == SCHED_RR ? "SCHED_RR" : "SCHED_OTHER");
    return 0;
}
