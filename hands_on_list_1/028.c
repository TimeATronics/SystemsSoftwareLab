/*
 * Q28. Find out the priority of your running program.
 *      Modify the priority with nice command.
 */
#include <stdio.h>
#include <sys/resource.h>

int main(void) {
    printf("nice value before = %d\n", getpriority(PRIO_PROCESS, 0));
    setpriority(PRIO_PROCESS, 0, 5);
    printf("nice value after setpriority(5) = %d\n", getpriority(PRIO_PROCESS, 0));
    return 0;
}
