/*
 * Q57. Print system limitations using sysconf():
 *   a. maximum length of arguments in the exec family (_SC_ARG_MAX)
 *   b. maximum number of simultaneous processes per user ID (_SC_CHILD_MAX)
 *   c. number of clock ticks (jiffies) per second (_SC_CLK_TCK)
 *   d. maximum number of open files (_SC_OPEN_MAX)
 *   e. size of a page (_SC_PAGESIZE)
 *   f. total number of pages in physical memory (_SC_PHYS_PAGES)
 *   g. currently available pages in physical memory (_SC_AVPHYS_PAGES)
 */
#include <stdio.h>
#include <unistd.h>

int main(void) {
    printf("a. max exec argument length          = %ld\n", sysconf(_SC_ARG_MAX));
    printf("b. max simultaneous processes/user   = %ld\n", sysconf(_SC_CHILD_MAX));
    printf("c. clock ticks (jiffies) per second  = %ld\n", sysconf(_SC_CLK_TCK));
    printf("d. max open files                    = %ld\n", sysconf(_SC_OPEN_MAX));
    printf("e. size of a page                    = %ld bytes\n", sysconf(_SC_PAGESIZE));
    printf("f. total pages in physical memory    = %ld\n", sysconf(_SC_PHYS_PAGES));
    printf("g. available pages in physical memory= %ld\n", sysconf(_SC_AVPHYS_PAGES));
    return 0;
}
